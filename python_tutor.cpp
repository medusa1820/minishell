#include <string.h>
#include <stdlib.h>

typedef enum e_ast_node_type
{
	AST_NODE_CMD,
	AST_NODE_PIPE
}	t_ast_node_type;

typedef enum e_redirect_type
{
	REDIRECT_STDIN,
	REDIRECT_STDOUT,
	REDIRECT_HERE_DOC,
	REDIRECT_STDOUT_APPEND
}	t_redirect_type;

typedef struct s_redirect
{
	t_redirect_type		type;
	char				*word;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_assignment
{
	char				*word;
	struct s_assignment	*next;
}	t_assignment;

typedef struct s_ast_node_content
{
	t_redirect		*stdin_redirect;
	t_redirect		*stdout_redirect;
	t_assignment	*assignments;
	char			**cmd;
}	t_ast_node_content;

typedef struct s_ast_node
{
	t_ast_node_type		type;
	t_ast_node_content	*content;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

int					main(void);
t_ast_node			*create_ast(void);
t_ast_node			*create_node(void);
void				init_node(t_ast_node *new_node, char *node_type, char **cmd, \
							t_ast_node *new_node_left, t_ast_node *new_node_right);
t_ast_node_content	*create_node_content(void);
void				init_node_content(char **cmd, t_ast_node *new_node);
static int			ft_word_count(char const *s, char c);
static int			ft_word_len(char const *s, char c, int i);
char				**ft_splits(char const *s, char c, int *word_count, char **strings);

int	main(void)
{
	t_ast_node	*head;

	head = create_ast();
	return (0);
}

t_ast_node	*create_ast(void)
{
	char		**cmd;
	t_ast_node	*new_node_left;
	t_ast_node	*new_node_right;
	t_ast_node	*new_node_head;

	cmd = ft_split("ls -la", ' ');
	new_node_left = create_node();
	init_node(new_node_left, "AST_NODE_CMD", cmd, NULL, NULL);
	cmd = ft_split("grep 1", ' ');
	new_node_right = create_node();
	init_node(new_node_right, "AST_NODE_CMD", cmd, NULL, NULL);
	new_node_head = create_node();
	init_node(new_node_head, "AST_NODE_PIPE", NULL, new_node_left, new_node_right);
	return (new_node_head);
}

t_ast_node	*create_node(void)
{
	t_ast_node	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (new_node == NULL)
		exit(EXIT_FAILURE);
	// new_node->type = NULL;
	new_node->content = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	init_node(t_ast_node *new_node, char *node_type, char **cmd, \
				t_ast_node *new_node_left, t_ast_node *new_node_right)
{
	new_node->type = *node_type;
	if (cmd)
	{
		new_node->content = create_node_content();
		init_node_content(cmd, new_node);
	}
	else
	{
		new_node->left = new_node_left;
		new_node->right = new_node_right;
	}
}

t_ast_node_content	*create_node_content(void)
{
	t_ast_node_content	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (new_node == NULL)
		exit(EXIT_FAILURE);
	new_node->stdin_redirect = NULL;
	new_node->stdout_redirect = NULL;
	new_node->assignments = NULL;
	new_node->cmd = NULL;
	return (new_node);
}

void	init_node_content(char **cmd, t_ast_node *new_node)
{
	new_node->content->cmd = cmd;
}

char	**ft_split(char const *s, char c)
{
	int		word_count;
	char	**strings;

	if (!s)
		return (0);
	word_count = ft_word_count(s, c);
	strings = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!strings)
		return (0);
	return (ft_splits(s, c, &word_count, strings));
}



char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	i;

	if (!s)
		return (0);
	if (start > strlen(s))
		return (strdup(""));
	if (len > strlen(s) - start)
		len = strlen(s) - start;
	sub_s = (char *)malloc(sizeof(*s) * (len + 1));
	if (!sub_s)
		return (0);
	i = 0;
	while (i < len)
	{
		*(sub_s + i++) = *(s + start++);
	}
	*(sub_s + i) = '\0';
	return (sub_s);
}

char	**ft_splits(char const *s, char c, int *word_count, char **strings)
{
	int	i;
	int	j;
	int	word_len;

	i = 0;
	j = 0;
	while (i < *word_count)
	{
		while (*(s + j) == c)
			j++;
		word_len = ft_word_len(s, c, j);
		*(strings + i) = ft_substr(s, j, word_len);
		if (!*(strings + i))
		{
			while (i-- > 0)
				free(*(strings + i));
			free(strings);
			return (0);
		}
		j = j + word_len;
		i++;
	}
	*(strings + i) = 0;
	return (strings);
}

static int	ft_word_count(char const *s, char c)
{
	int	i;
	int	word_count;

	i = 0;
	word_count = 0;
	while (s && *(s + i) != '\0')
	{
		if (*(s + i) == c)
			i++;
		else
		{
			word_count++;
			while (*(s + i) != '\0' && *(s + i) != c)
				i++;
		}
	}
	return (word_count);
}

static int	ft_word_len(char const *s, char c, int j)
{
	int	start;

	start = j;
	while (*(s + j) != 0 && *(s + j) != c)
		j++;
	return (j - start);
}

