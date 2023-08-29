
// Define your token and AST structures here

t_ast_node *parse_command(t_token **tokens, int *token_count);
t_ast_node *parse_pipeline(t_token **tokens, int *token_count);


char **ft_realloc_strings(char **ptr, size_t old_count, size_t new_count)
{
    char **new_ptr;

	if (!ptr)
	{
		new_ptr = (char **) ft_calloc(new_count + 2, sizeof(char *));
		if (!new_ptr)
		{
        	perror("Memory allocation error");
        	exit(1);
		}
		return new_ptr;
	}
    if (new_count == 0)
    {
        // Free the old array and return NULL
        for (size_t i = 0; i < old_count; ++i)
            free(ptr[i]);
        free(ptr);
        return NULL;
    }
    
    // Allocate memory for the new array of strings
    new_ptr = ft_calloc(new_count, sizeof(char *));
    if (new_ptr == NULL)
        return ptr;  // Return the old array if allocation fails
    
    // Copy the existing strings to the new array
    size_t copy_count = old_count < new_count ? old_count : new_count;
    for (size_t i = 0; i < copy_count; ++i)
    {
        new_ptr[i] = ft_strdup(ptr[i]);
        if (new_ptr[i] == NULL)
        {
            // Allocation failed for one of the strings, clean up and return
            for (size_t j = 0; j < i; ++j)
                free(new_ptr[j]);
            free(new_ptr);
            return ptr;
        }
    }
    
    // Free the old array and return the new array
    for (size_t i = 0; i < old_count; ++i)
        free(ptr[i]);
    free(ptr);
    return new_ptr;
}

void free_ast(t_ast_node *node);

t_ast_node *create_command_node(t_ast_node_content *content) {
	t_ast_node *node = (t_ast_node *)ft_calloc(sizeof(t_ast_node));
	if (!node) {
		perror("Memory allocation error");
		exit(1);
	}
	node->type = AST_NODE_CMD;
	node->content = content;
	node->left = NULL;
	node->right = NULL;
	return node;
}

t_ast_node *create_pipe_node(t_ast_node *left, t_ast_node *right) {
	t_ast_node *node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node) {
		perror("Memory allocation error");
		exit(1);
	}
	node->type = AST_NODE_PIPE;
	node->content = NULL;
	node->left = left;
	node->right = right;
	return node;
}

t_ast_node_content *parse_command_content(t_token **tokens, int *token_count)
{
	t_ast_node_content *content = (t_ast_node_content *)malloc(sizeof(t_ast_node_content));
	// if (!content) {
	// 	perror("Memory allocation error");
	// 	exit(1);
	// }
	// Initialize content fields
	content->stdin_redirect = NULL;
	content->stdout_redirect = NULL;
	content->assignments = NULL;
	content->cmd = NULL;  // To be filled with the command parts
	if (*token_count >= 0 && (*tokens)[*token_count - 1].type == TOKEN_PIPE)
		return NULL;
	// Parse command content, redirections, and assignments
	// Iterate through tokens, identify stdin/stdout redirections, assignments, and command parts

	// Example of parsing a command:
	content->cmd = (char **)malloc(sizeof(char *) * (*token_count + 1)); //later work on passing the amount of word instead of token_count to optimize memory allocation
	int cmd_index = 0;
	--(*token_count);
		printf("token_count:%d\n", *token_count);
	while (*token_count >= 0 && (*tokens)[*token_count].type != TOKEN_PIPE) {
		content->cmd[cmd_index] = ft_strdup((*tokens)[*token_count].value);
		// (*tokens)++;
		(*token_count)--;
		cmd_index++;
	}
	content->cmd[cmd_index] = NULL;  // Null-terminate the command array
	return content;
}

t_ast_node *parse_command(t_token **tokens, int *token_count) {
	// Parse the command content and create the AST node
	t_ast_node_content *content = parse_command_content(tokens, token_count);; // Parse command content, redirections, assignments
	return create_command_node(content);
}

t_ast_node *parse_pipeline(t_token **tokens, int *token_count) {
	t_ast_node *left;

	if (*token_count > 0 && (*tokens)[*token_count - 1].type != TOKEN_PIPE)
		left = parse_command(tokens, token_count);

	// Check if there's a pipe operator
	if (*token_count > 0 && (*tokens)[*token_count - 1].type == TOKEN_PIPE && strcmp((*tokens)[*token_count - 1].value, "|") == 0) {
		// (*tokens)++; // Consume the pipe operator
		(*token_count)--;
		t_ast_node *right = parse_pipeline(tokens, token_count);
		return create_pipe_node(left, right);
	}
	
	return left;
}

void free_ast(t_ast_node *node) {
	if (!node) {
		return;
	}

	if (node->type == AST_NODE_CMD) {
		// Free command content
	} else if (node->type == AST_NODE_PIPE) {
		free_ast(node->left);
		free_ast(node->right);
	}

	free(node);
}

void print_ast_node(t_ast_node *node, int level) {
	if (!node->content)
	{
		printf("hi\n");
		return;

	}

	for (int i = 0; i < level; i++) {
		printf("    "); // Indentation for readability
	}


	if (node->type == AST_NODE_CMD) {
		printf("Node type: AST_NODE_CMD\n");
		if (node->content) {
			printf("Content:\n");
			if (node->content->cmd) {
				printf("    Command:");
				for (int i = 0; node->content->cmd[i] != NULL; i++) {
					printf(" %s", node->content->cmd[i]);
				}
				printf("\n");
			}
			// Print redirections and assignments if needed
		}
	} else if (node->type == AST_NODE_PIPE) {
		printf("Node type: AST_NODE_PIPE\n");
	}

	print_ast_node(node->left, level + 1);
	print_ast_node(node->right, level + 1);
}

void print_ast(t_ast_node *root) {
	printf("Left child:\n");

	print_ast_node(root->left, 1);
	printf("Right child:\n");
	print_ast_node(root->right, 1);
}