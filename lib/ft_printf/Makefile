NAME			=	lib_libft_printf.a

SRCS			=	ft_printf.c \
					ft_putchar.c \
					ft_putstr.c \
					ft_put_ptr.c \
					ft_put_nmbr_hex_lower.c \
					ft_put_u_nmbr_base.c \
					ft_u_nmbr_base_len.c \
					ft_put_nmbr.c \
					ft_nmbr_base_len.c \
					ft_put_nmbr_unsigned.c \
					ft_put_nmbr_hex_upper.c

OBJS			=	$(SRCS:.c=.o)

CC				=	gcc
RM				=	rm -f
CFLAGS			=	-Wall -Wextra -Werror
AR				=	ar
ARFLAGS 		=	rcs

LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a

%.o:				%.c
					$(CC) $(CFLAGS) -c $< -o $@

all:				$(NAME)

$(NAME):			$(LIBFT) $(OBJS)
				cp	$(LIBFT) $(NAME)
					$(AR) $(ARFLAGS) $(NAME) $(OBJS)

$(LIBFT):
					make -C $(LIBFT_PATH) bonus

clean:
					make -C $(LIBFT_PATH) clean
					$(RM) $(OBJS)

fclean:				clean
					make -C $(LIBFT_PATH) fclean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re libft