NAME				:=	minishell

CC					:=	gcc

CFLAGS				:=	-Wall -Werror -Wextra
CFLAGS				+=	-g
# CFLAGS				+=	-fsanitize=address

LDFLAGS				:=	-g
# LDFLAGS				+=	-fsanitize=address

MINISHELL_SRCS		=	./main.c \

DATA_INIT_SRCS		=	./00_data_init/envp_ll_init.c \
						./00_data_init/envp_ll_utils.c \
						./00_data_init/envp_local_init.c \
						./00_data_init/envp_local_utils.c \
						./00_data_init/pipe_data.c

LEXER_SRCS			=	./01_lexer/lexer_generation.c \
						./01_lexer/free_print_tokens.c \
						./01_lexer/tokenization_trimming_utils.c \
						./01_lexer/tokenization_utils.c \
						./01_lexer/tokens_type.c

PARSER_SRCS			=	./02_parser/cmd_content_utils.c \
						./02_parser/creat_node_content.c \
						./02_parser/creat_node.c \
						./02_parser/free_ast.c \
						./02_parser/parsing.c \
						./02_parser/print_ast.c \
						./02_parser/redirect_content_utils.c 

EXPANDER_SRCS		=	./03_expander/expander.c

EXECUTOR_SRCS		=	./04_executor/execute_ast0.c \
						./04_executor/execute_ast1.c \
						./04_executor/child_process.c \
						./04_executor/child_process_utils0.c \
						./04_executor/child_process_utils1.c \
						./04_executor/child_process_utils2.c \
						./04_executor/exit_code_handler0.c \
						./04_executor/signals0.c \
						./04_executor/signals1.c \
						./04_executor/signals2.c

UTILS_SRCS			=	./05_utils/create_ast.c \
						./05_utils/print_ast.c \
						./05_utils/free_ast.c \
						./05_utils/exit_utils0.c \
						./05_utils/exit_utils1.c \
						./05_utils/get_next_line.c

BUILTINS_SRCS		=	./06_builtins/builtin_calls.c \
						./06_builtins/echo.c \
						./06_builtins/export.c \
						./06_builtins/unset.c \
						./06_builtins/env.c \
						./06_builtins/pwd.c \
						./06_builtins/exit.c \
						./06_builtins/builtin_utils.c \
						./06_builtins/cd.c \
						# ./06_builtins/cd_new.c \

ALL_SRCS			:=	$(MINISHELL_SRCS) \
						$(DATA_INIT_SRCS) \
						$(LEXER_SRCS) \
						$(PARSER_SRCS) \
						$(EXPANDER_SRCS) \
						$(EXECUTOR_SRCS) \
						$(UTILS_SRCS) \
						$(BUILTINS_SRCS)

HEADERS				:=	-I ./include
# HEADERS				+=	-I ./05_utils
HEADERS				+=	-I $(shell brew --prefix readline)/include # comment this for use in Debian
# HEADERS				+=	-I ../LeakSanitizer

LDFLAGS				+=	-L ./lib/ft_printf -lft_ft_printf
LDFLAGS				+=	-lreadline -L $(shell brew --prefix readline)/lib
# LDFLAGS				+=	-lreadline # for Debian
# LDFLAGS				+=	-L ../LeakSanitizer -llsan -lstdc++ -Wno-gnu-include-next

LIBFT_FT_PRINTF		:=	lib/ft_printf/libft_ft_printf.a
LIBFT_FT_PRINTF_DIR	:=	./lib/ft_printf

OBJS				=	$(ALL_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT_FT_PRINTF) $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) \
	&& echo "Compilation of $(NAME) successful"

%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFT_FT_PRINTF):
	${MAKE} -C $(LIBFT_FT_PRINTF_DIR) -j

re: fclean all

fclean: clean
	rm -f $(NAME)

clean:
	${MAKE} -C $(LIBFT_FT_PRINTF_DIR) fclean
	rm -f $(OBJS)

leaks:
	@valgrind	--track-fds=yes \
				--track-origins=yes \
				--tool=memcheck \
				--trace-children=yes \
				--leak-check=full \
				--show-leak-kinds=all \
				-s \
				./minishell < infile cat | grep PATH | grep /usr > outfile

.PHONY: all clean fclean re leaks
