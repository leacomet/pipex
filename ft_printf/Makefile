NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRCS = ft_printf.c ft_printf_csdiu.c ft_printf_xXp.c\

OBJS = ${SRCS:.c=.o}

AR = ar src

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

${NAME}: ${OBJS}
		$(AR) $(NAME) $(OBJS)

all: ${NAME}

clean:
	-rm -f ${OBJS} ${OBJS_BONUS}

fclean: clean
	-rm -f ${NAME}

re: fclean all

.PHONY: all bonus clean fclean re
