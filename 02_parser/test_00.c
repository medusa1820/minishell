
#include "minishell.h"

// Function to create a new AST node
t_ast_node *create_ast_node(t_ast_node_type type) {
    t_ast_node *node = (t_ast_node *)malloc(sizeof(t_ast_node));
    node->type = type;
    node->content = (t_ast_node_content *)malloc(sizeof(t_ast_node_content));
    node->content->stdin_redirect = NULL;
    node->content->stdout_redirect = NULL;
    node->content->assignments = NULL;
    node->content->cmd = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to parse assignments
t_assignment *parse_assignments() {
    // Implement parsing logic for assignments
    // Return a linked list of assignments
    return NULL;
}

// Function to parse redirects
t_redirect *parse_redirect() {
    // Implement parsing logic for redirects
    // Return a linked list of redirects
    return NULL;
}

// Function to parse command words
char **parse_command_words() {
    // Implement parsing logic for command words
    // Return an array of strings (command words)
    return NULL;
}

// Function to parse a single command
t_ast_node *parse_command() {
    t_ast_node *node = create_ast_node(AST_NODE_CMD);

    // Parse redirects, assignments, and command
    node->content->stdin_redirect = parse_redirect();
    node->content->stdout_redirect = parse_redirect();
    node->content->assignments = parse_assignments();
    node->content->cmd = parse_command_words();

    return node;
}

// Function to parse a single pipe
t_ast_node *parse_pipe() {
    t_ast_node *node = create_ast_node(AST_NODE_PIPE);

    // Parse left and right sub-trees
    node->left = parse_command();
    node->right = parse_command();

    return node;
}

// Function to start parsing
t_ast_node *parse() {
    // You might start with the highest-level grammar rule
    return parse_pipe();
}

// Function to free memory used by AST nodes
void free_ast(t_ast_node *node) {
    if (node == NULL) {
        return;
    }
    free_ast(node->left);
    free_ast(node->right);
    free(node->content->cmd);
    free(node->content);
    free(node);
}

// int main() {
//     // Tokenize the input string using the lexer

//     // Parse the tokens and create the AST
//     t_ast_node *root = parse();

//     // ... Further processing and execution

//     // Free the memory used by the AST
//     free_ast(root);

//     return 0;
// }

// void	print_cmd(char **cmd)
// {
// 	while (*cmd)
// 	{
// 		printf("%s\n", *cmd);
// 		cmd++;
// 	}
// }

// void	assign_value(t_split *sp, char *input_string)
// {
// 	sp->input_copy = ft_strdup(input_string);
// 	sp->result = ft_calloc(sizeof(char *), ft_strlen (sp->input_copy));// it should be according to number of pipe sign
// 	if (!sp->result)
// 		exit(EXIT_FAILURE);
// 	sp->token_start = sp->input_copy;
// 	sp->p = sp->input_copy;
// 	sp->index = 0;
// 	sp->inside_quote = 0;
// 	sp->quote_char = '\0';
// }

// void	parse_string(t_split *sp)
// {
// 	while (*sp->p != '\0')
// 	{
// 		if (*sp->p == '"' || *sp->p == '\'')
// 		{
// 			if (sp->quote_char == '\0' || sp->quote_char == *sp->p)
// 			{
// 				sp->inside_quote = !sp->inside_quote;
// 				sp->quote_char = *sp->p;
// 			}
// 		}
// 		else if (*sp->p == ' ' && !sp->inside_quote)
// 		{
// 			*sp->p = '\0';
// 			if (sp->token_start[0] != '\0')
// 			{
// 				sp->result[sp->index++] = ft_strdup(sp->token_start);
// 			}
// 			sp->token_start = sp->p + 1;
// 		}
// 		++sp->p;
// 	}
// }

// char	**sanitize(char **string, int len)
// {
// 	int		i;
// 	char	*buff;

// 	i = 0;
// 	while (i < len)
// 	{
// 		if (string[i][0] == '\'')
// 		{
// 			buff = ft_strdup(string[i]);
// 			ft_strlcpy(string[i], buff + 1, ft_strlen(string[i]) - 1);
// 			free(buff);
// 		}
// 		i++;
// 	}
// 	return (string);
// }

// char	**split_string(char *input_string)
// {
// 	t_split	sp;

// 	assign_value(&sp, input_string);
// 	parse_string(&sp);
// 	if (*sp.token_start != '\0')
// 	{
// 		sp.result[sp.index++] = ft_strdup(sp.token_start);
// 	}
// 	sp.result[sp.index] = 0;
// 	sanitize(sp.result, sp.index);
// 	return (sp.result);
// }
