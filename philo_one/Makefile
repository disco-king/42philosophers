NAME = philo

SRCS = main.c init.c eat.c \
			simulation.c lib_funcs.c \
			utils.c

HEADER = philos.h

OBJS = $(SRCS:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror

%.o: %.c
	${CC} ${FLAGS} -c $< -o $@

all: ${NAME} ${OBJS}

$(NAME): $(OBJS) $(HEADER)
		$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
		rm -rf $(OBJS)

fclean:
		rm -rf $(OBJS) $(NAME)

re:		fclean $(NAME)