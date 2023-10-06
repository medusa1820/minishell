/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musenov <musenov@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:41:26 by nnavidd           #+#    #+#             */
/*   Updated: 2023/10/06 21:02:32 by musenov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bool	init_shell(t_minishell *shell, t_pipe *data)
bool	init_shell(t_minishell *shell)
{
	shell->ast_root = NULL;
	shell->tokens = NULL;
	shell->free_lexer_token_len = 0;
	shell->token_len = 0;
	shell->seg_end = 0;
	shell->head = 0;
	shell->cmd_count = 0;
	shell->index = 0;
	shell->cmd_index = 0;
	shell->space_flag = false;
	shell->line = NULL;
	shell->data = NULL;
	// shell->exit_code_dummy = data->exit_code;
	init_envp_linked_list(shell);
	envp_ll_to_envp_local(shell);
	return (true);
}

t_ast_node	*create_command_node(t_ast_node_content *content)
{
	t_ast_node	*node;

	node = (t_ast_node *)ft_calloc(1, sizeof(t_ast_node));
	if (!node)
	{
		perror ("Memory allocation error"); //error handeling
		exit(1);
	}
	node->type = AST_NODE_CMD;
	node->content = content;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast_node	*create_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	node = (t_ast_node *)ft_calloc(1, sizeof(t_ast_node));
	if (!node)
	{
		perror("Memory allocation error"); //error handling
		exit(1);
	}
	node->type = AST_NODE_PIPE;
	node->content = NULL;
	node->left = left;
	node->right = right;
	return (node);
}

t_redirect_type	redirect_type(char *str)
{
	t_redirect_type	type;

	type = UNDEFINED_TYPE;
	if (str[0] == '>' && str[1] == '>')
		type = REDIRECT_STDOUT_APPEND;
	else if (str[0] == '<' && str[1] == '<')
		type = REDIRECT_HERE_DOC;
	else if (str[0] == '<' && str[1] == 0)
		type = REDIRECT_STDIN;
	else if (str[0] == '>' && str[1] == 0)
		type = REDIRECT_STDOUT;
	// if (str)
	// 	free(str);
	return (type);
}

t_parser_state	add_redirect(t_redirect **redirect, \
t_redirect *new_redirection)
{
	t_redirect		*last_redirection;

	if (redirect == NULL || new_redirection == NULL)
		return (PARSER_FAILURE);
	if (*redirect == NULL)
		*redirect = new_redirection;
	else
	{
		last_redirection = *redirect;
		while (last_redirection->next != NULL)
			last_redirection = last_redirection->next;
		last_redirection->next = new_redirection;
	}
	return (PARSER_SUCCESS);
}

t_parser_state	parse_redirection(t_ast_node_content **content, t_minishell *sh)
{
	t_redirect		*new_redirection;
	t_redirect_type	type;
	t_parser_state	ret;

	new_redirection = NULL;
	new_redirection = (t_redirect *)ft_calloc(1, sizeof(t_redirect));
	if (!new_redirection)
		return (perror("Memory allocation error"), PARSER_FAILURE);
	type = redirect_type(sh->tokens[sh->head].value); // Set the type of redirection
	new_redirection->type = type;
	new_redirection->word = ft_strdup(sh->tokens[sh->head + 1].value); // put next head in value of this node
	free(sh->tokens[sh->head + 1].value);
	sh->tokens[sh->head + 1].value = NULL;
	new_redirection->next = NULL;
	if (type == REDIRECT_STDIN || type == REDIRECT_HERE_DOC)
		ret = add_redirect(&((*content)->stdin_redirect), new_redirection);
	if (type == REDIRECT_STDOUT || type == REDIRECT_STDOUT_APPEND)
		ret = add_redirect(&((*content)->stdout_redirect), new_redirection);
	if (ret == PARSER_FAILURE)
		return (PARSER_FAILURE);
	sh->head += 2;
	sh->token_len -= 2;
	return (PARSER_SUCCESS);
}

t_parser_state parse_assignment(t_ast_node_content **content, t_minishell *sh)
{
	t_assignment	*new_assignment;
	t_assignment	*last_assignment;

	new_assignment = (t_assignment *)ft_calloc(1, sizeof(t_assignment));
	if (!new_assignment)
		return (perror("Memory allocation error"), PARSER_FAILURE);
	new_assignment->word = ft_strdup(sh->tokens[sh->head].value);
	if (!new_assignment->word)
		return (PARSER_FAILURE);
	free(sh->tokens[sh->head].value);
	sh->tokens[sh->head].value = NULL;
	new_assignment->next = NULL;
	if ((*content)->assignments == NULL)
		(*content)->assignments = new_assignment;
	else
	{
		last_assignment = (*content)->assignments;
		while (last_assignment->next != NULL)
			last_assignment = last_assignment->next;
		last_assignment->next = new_assignment;
	}
	sh->head++;
	sh->token_len--;
	return (PARSER_SUCCESS);
}
t_parser_state	parse_cmd_word(t_ast_node_content **content, t_minishell *sh);
t_parser_state	feed_remained_cmd_tokens(t_ast_node_content **content, t_minishell *sh)
{
	int	tmp_head;
	int	tmp_seg_end;

	tmp_head = sh->head;
	tmp_seg_end = sh->seg_end;
	while (tmp_head < tmp_seg_end && sh->tokens[tmp_head].type != TOKEN_REDIRECT)
	{
		if (sh->tokens[tmp_head].type == TOKEN_ASSIGNMENT)
			sh->tokens[tmp_head].type = TOKEN_WORD;
		tmp_head++;
	}
	return (parse_cmd_word(content, sh));
}

size_t count_strings(char* strings[])
{
	size_t count = 0;
	if (strings != NULL)
	{
		while (strings[count] != NULL)
			count++;
	}
	return count;
}

char **ft_realloc_strings(char **ptr, size_t old_count, size_t new_count)
{
	char	**new_ptr;
	size_t	copy_count;
	size_t	i;

	if (!ptr)
	{
		new_ptr = (char **) ft_calloc(new_count + 2, sizeof(char *));
		if (!new_ptr)
			return (freeing_cmd(new_ptr), NULL);
		return (new_ptr);
	}
	new_ptr = ft_calloc(old_count + new_count + 2, sizeof(char *));
	if (new_ptr == NULL)
			return (freeing_cmd(ptr), NULL);
	copy_count = old_count;// < new_count ? old_count : new_count;
	i = 0;
	while (i < copy_count)
	{
		new_ptr[i] = ft_strdup(ptr[i]);
		if (new_ptr[i] == NULL)
			return (freeing_cmd(new_ptr), NULL);
		i++;
	}
	freeing_cmd(ptr);
	return (new_ptr);
}
// HI "HI" ""HI "H"I
t_parser_state	parse_cmd_word(t_ast_node_content **content, t_minishell *sh)
{
	t_parser_state	ret;

	// while (sh->space_flag && (sh->tokens[sh->head].value = '\0'))
	// {
	// 	sh->head++;
	// 	sh->token_len--;	
	// }
	sh->cmd_count = sh->head - 1;
	ret = PARSER_FAILURE;
	if (sh->head < sh->seg_end && sh->tokens[sh->head].type != TOKEN_WORD)
		return (ret);
	while (++sh->cmd_count < sh->seg_end && \
			sh->tokens[sh->cmd_count].type == TOKEN_WORD)
	{
		// if ((sh->tokens[sh->head].value = '\0'))
		sh->index++;
	}
	(*content)->cmd = ft_realloc_strings((*content)->cmd, \
				count_strings((*content)->cmd), sh->index);
	sh->index = count_strings((*content)->cmd);
	while (sh->head < sh->seg_end && sh->tokens[sh->head].type == TOKEN_WORD)
	{
		(*content)->cmd[sh->index] = ft_strdup(sh->tokens[sh->head].value);
		(*content)->cmd[sh->index + 1] = NULL;
		if (!(*content)->cmd[sh->index++])
			return (PARSER_FAILURE);
		free(sh->tokens[sh->head].value);
		sh->tokens[sh->head++].value = NULL;
		sh->token_len--;
		ret = PARSER_SUCCESS;
	}
	sh->index = 0;
	return (ret);
}


t_parser_state	parse_sufix_cmd(t_ast_node_content **content, t_minishell *sh)
{
	t_parser_state	ret;

	ret = PARSER_FAILURE;
	while (true)
	{
		if (sh->seg_end >= 2 && sh->head + 1 < sh->seg_end && \
		sh->tokens[sh->head].type && \
		sh->tokens[sh->head].type == TOKEN_REDIRECT && \
		(sh->tokens[sh->head + 1].type == TOKEN_ASSIGNMENT || \
		sh->tokens[sh->head + 1].type == TOKEN_WORD )) //later check variable of token,would better assign to the EOF and PIP
		{
			ret = parse_redirection(content, sh);
			continue ;
		}
		else if (sh->head <= sh->token_len && (sh->tokens[sh->head].type == TOKEN_ASSIGNMENT || \
		sh->tokens[sh->head].type == TOKEN_WORD))
		{
			ret = feed_remained_cmd_tokens(content, sh);
			continue ;
		}
		else
			break ;
	}
	return (ret);
}

t_parser_state	parse_prefix_cmd(t_ast_node_content **content, t_minishell *sh)
{
	t_parser_state	ret;

	ret = PARSER_FAILURE;
	while (true)
	{
		if (sh->seg_end >= 2 && sh->head + 1 < sh->seg_end && \
		sh->tokens[sh->head].type && \
		sh->tokens[sh->head].type == TOKEN_REDIRECT && \
		(sh->tokens[sh->head + 1].type == TOKEN_ASSIGNMENT || \
		sh->tokens[sh->head + 1].type == TOKEN_WORD )) //later check variable of token,would better assign to the EOF and PIP
		{
			ret = parse_redirection(content, sh);
			continue ;
		}
		else if (sh->head <= sh->token_len && \
				sh->tokens[sh->head].type == TOKEN_ASSIGNMENT)
		{
			ret = parse_assignment(content, sh);
			continue ;
		}
		else
			break ;
	}
	return (ret);
}

void	finding_segment_head(t_minishell *sh)
{
	sh->head = sh->token_len - 1;
	sh->seg_end = sh->token_len;
	while (sh->head >= 0)
	{
		if (sh->tokens[sh->head].type == TOKEN_PIPE)
			break ;
		if ((sh->head - 1) >= 0 && sh->tokens[sh->head - 1].type == TOKEN_PIPE)
			break ;
		sh->head--;
	}
	if (sh->head < 0)
		sh->head = 0;
}

t_parser_state	parse_command_content(t_ast_node_content **content, t_minishell *sh)
{
	t_parser_state	ret;

	if (sh->token_len >= 0 && sh->tokens[sh->token_len - 1].type == TOKEN_PIPE)
		return (free(*content),*content = NULL, PARSER_SYNTAX_ERROR);
	finding_segment_head(sh);
	while (sh->head < sh->seg_end) //&& sh->tokens[sh->head].type != TOKEN_PIPE)
	{
		ret = parse_prefix_cmd(content, sh);
		if (ret == PARSER_FAILURE)
		{
			ret = parse_cmd_word(content, sh);
			if (ret == PARSER_FAILURE)
				return (ret);
		}
		else
		{
			if (parse_cmd_word(content, sh) == PARSER_FAILURE)
				return (ret);
		}
		parse_sufix_cmd(content, sh);
	}
	return (PARSER_SUCCESS);
}

void	free_content(t_ast_node_content *content)
{
	if (content == NULL)
		return ;
	if (content->assignments)
		freeing_assignment(content->assignments);
	if (content->stdin_redirect)
		freeing_redirection(content->stdin_redirect);
	if (content->stdout_redirect)
		freeing_redirection(content->stdout_redirect);
	if (content->cmd)
		freeing_cmd(content->cmd);
		
}

t_ast_node *parse_command(t_minishell *sh)
{
	int					ret;
	t_ast_node_content	*content;

	content = (t_ast_node_content *)ft_calloc(1, sizeof(t_ast_node_content));
	if (!content)
	{
		perror("Memory allocation error"); //error handling
		exit(1);
	}
	content->stdin_redirect = NULL;
	content->stdin_redirect = NULL;
	content->assignments = NULL;
	content->cmd = NULL;
	ret = parse_command_content(&content, sh);
	if (ret)
		free_content(content);
	if (content == NULL || ret)
		return (free(content), NULL);  // Return NULL if command content is empty (due to PIPE)
	return (create_command_node(content));
}

t_ast_node *parse_pipeline(t_minishell *sh)
{
	t_ast_node	*left;
	t_ast_node	*right;

	right = parse_command(sh);
	if (sh->token_len > 0 && right != NULL && sh->tokens[sh->token_len - 1].type == TOKEN_PIPE)
	{
		free(sh->tokens[sh->token_len - 1].value);
		sh->tokens[sh->token_len - 1].value = NULL;
		sh->token_len--;
		left = parse_pipeline(sh);
		return (create_pipe_node(left, right));
	}
	return (right);
}

void	freeing_cmd(char **cmd)
{
	int i;

	if (cmd == NULL)
		return ;
	i = 0;
	while (cmd[i] != NULL)
	{
		free(cmd[i]);
		cmd[i] = NULL;
		i++;
	}
	free(cmd);
	cmd = NULL;
}

void	freeing_redirection(t_redirect *ptr)
{
	t_redirect	*temp;

	while (ptr != NULL)
	{
		temp = ptr;
		ptr = ptr->next;
		free(temp->word);
		temp->word = NULL;
		free(temp);
		temp = NULL;
	}
	free(ptr);
	ptr = NULL;
}

void	freeing_assignment(t_assignment *ptr)
{
	t_assignment	*temp;

	while (ptr != NULL)
	{
		temp = ptr;
		ptr = ptr->next;
		free(temp->word);
		temp->word = NULL;
		free(temp);
		temp = NULL;
	}
	free(ptr);
	ptr = NULL;
}


// HI "HI" ""HI "H"I

int	free_ast(t_ast_node **node_ptr)
{
	// exit(1);
	if (!(*node_ptr))
	{
		printf("hi\n");
		return (1);
	}
	if ((*node_ptr)->type == AST_NODE_CMD)
	{
		if ((*node_ptr)->content)
		{
			if ((*node_ptr)->content->cmd)
				freeing_cmd((*node_ptr)->content->cmd);
			if ((*node_ptr)->content->stdin_redirect)
				freeing_redirection((*node_ptr)->content->stdin_redirect);
			if ((*node_ptr)->content->stdout_redirect)
				freeing_redirection((*node_ptr)->content->stdout_redirect);
			if ((*node_ptr)->content->assignments)
				freeing_assignment((*node_ptr)->content->assignments);
		}
		free((*node_ptr)->content); // (*node_ptr)->content = NULL;
	}
	else if ((*node_ptr)->type == AST_NODE_PIPE)
	{
		free_ast(&((*node_ptr)->left));
		free_ast(&((*node_ptr)->right));
		(*node_ptr)->left = NULL;
		(*node_ptr)->right = NULL;
	}
	return (free(*node_ptr), *node_ptr = NULL, 0);
}

void print_ast_node(t_ast_node *node, int level, char x)
{
	if (x == 'x')
		printf("\n***************** AST ****************\n");
	if (node == NULL)
		return;
	for (int i = 0; i < level; i++)
		printf("  ");
	if (x == 'l')
		printf(BLUE "Left child:\n");
	if (x == 'r')
		printf(BLUE "Right child:\n" RESET);
	for (int i = 0; i < level; i++)
		printf("    ");
	if (node->type == AST_NODE_CMD)
	{
		printf(RED "Node type:" RESET ORG" AST_NODE_CMD\n" RESET);
		if (node->content)
		{
			for (int i = 0; i < level; i++)
				printf("    ");
			printf(RED "Content:\n"RESET);
			if (node->content->cmd)
			{
				for (int i = 0; i < level; i++)
					printf("    ");
				printf("Command:");
				for (int i = 0; node->content->cmd[i] != NULL; i++)
					printf(ORG " %s" RESET, node->content->cmd[i]);
				printf("\n");
			}
			if (node->content->assignments)
			{
				for (int i = 0; i < level; i++)
					printf("    ");
				printf("Assignments:");
				for (t_assignment *tmp = node->content->assignments; tmp; tmp = tmp->next)
					printf(ORG " %s" RESET, tmp->word);
				printf("\n");
			}
			if (node->content->stdin_redirect)
			{
				for (int i = 0; i < level; i++)
					printf("    ");
				printf("stdin_redirect:");
				for (t_redirect *tmp = node->content->stdin_redirect; tmp; tmp = tmp->next)
					printf(ORG " %s" RESET, tmp->word);
				printf("\n");
			}
			if (node->content->stdout_redirect)
			{
				for (int i = 0; i < level; i++)
					printf("    ");
				printf("stdout_redirect:");
				for (t_redirect *tmp = node->content->stdout_redirect; tmp; tmp = tmp->next)
					printf(ORG " %s" RESET, tmp->word);
				printf("\n");
			}
		}
	}
	else if (node->type == AST_NODE_PIPE)
		printf(RED "Node type:"RESET ORG" AST_NODE_PIPE\n" RESET);
	print_ast_node(node->left, level + 1, 'l');
	print_ast_node(node->right, level + 1, 'r');
}
