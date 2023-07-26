NAME				:=	minishell

CC					:=	gcc

CFLAGS				:=	-Wall -Werror -Wextra -g3
CFLAGS				+=	-fsanitize=address

LDFLAGS				:=	-g3
LDFLAGS				+=	-fsanitize=address

MINISHELL_SRCS		=	./main.c \
						./minishell.c \

LEXER_SRCS			=	./01_lexer/lexer0.c \
						./01_lexer/lexer1.c

PARSER_SRCS			=	./02_parser/parser0.c \
						./02_parser/parser1.c \

ALL_SRCS			=	$(MINISHELL_SRCS) \
						$(LEXER_SRCS) \
						$(PARSER_SRCS) \

HEADERS				:=	-I ./include
HEADERS				+=	-I $(brew --prefix readline)/include 
HEADERS				+=	-I ../LeakSanitizer

LDFLAGS				+=	-L ./lib/ft_printf -l_libft_printf
LDFLAGS				+=	-L $(shell brew --prefix readline)/lib -lreadline
LDFLAGS				+=	-L ../LeakSanitizer -llsan -lc++ -Wno-gnu-include-next

OBJS				=	$(ALL_SRCS:.c=.o)

all: $(NAME)

$(NAME): libft_printf $(OBJS)
	$(CC) $(CFLAGS) $(ALL_SRCS) $(HEADERS) -o $(NAME) $(LDFLAGS) \
	&& echo "Compilation of $(NAME) successful"

LIBFT_PRINTF_DIR	=	./lib/ft_printf

libft_printf:
	${MAKE} -C $(LIBFT_PRINTF_DIR) -j

re: fclean all

fclean: clean
	rm -f $(NAME)

clean: ${MAKE} -C $(LIBFT_PRINTF_DIR) fclean
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

.PHONY: all clean fclean re libft_printf leaks
