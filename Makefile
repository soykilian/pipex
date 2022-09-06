NAME = pipex

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address


SRCS = pipex.c utils.c utils2.c

OBJS = ${SRCS:.c=.o}

RM = rm -r

all: ${NAME}

%.o:%.c
	${CC} ${CFLAGS} -o $@ -c $^

$(NAME): ${OBJS}
	${CC} ${CFLAGS} ${INCLUDE} ${OBJS} -o ${NAME}

clean :
	${RM} ${OBJS}

fclean:  clean
	${RM} ${NAME}

re: fclean all
.PHONY: clean re fclean all
