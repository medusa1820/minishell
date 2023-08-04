NAME				:=	minishell

CC					:=	gcc

CFLAGS				:=	-Wall -Werror -Wextra
CFLAGS				+=	-g3
CFLAGS				+=	-fsanitize=address

LDFLAGS				:=	-g3
LDFLAGS				+=	-fsanitize=address

MINISHELL_SRCS		=	./main.c \
						./create_ast.c \
						./print_ast.c \
						./free_ast.c \
						./execute_ast.c \
						./child_process.c \
						./child_process_utils0.c \
						./child_process_utils1.c

LEXER_SRCS			=	./01_lexer/lexer0.c \

PARSER_SRCS			=	./02_parser/parser0.c \

ALL_SRCS			:=	$(MINISHELL_SRCS) \
						$(LEXER_SRCS) \
						$(PARSER_SRCS) \

HEADERS				:=	-I ./include
HEADERS				+=	-I $(shell brew --prefix readline)/include
HEADERS				+=	-I ../LeakSanitizer

LDFLAGS				+=	-L ./lib/ft_printf -lft_ft_printf
LDFLAGS				+=	-lreadline -L $(shell brew --prefix readline)/lib
LDFLAGS				+=	-L ../LeakSanitizer -llsan -lc++ -Wno-gnu-include-next

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
				--tool=memcheck \
				--trace-children=yes \
				-s \
				./minishell

.PHONY: all clean fclean re leaks

# --show-leak-kinds=all \
# --leak-check=full \
# --track-origins=yes \