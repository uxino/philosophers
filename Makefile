NAME	=	philo
SRC		=	ft_atoi.c philo.c utils.c
OBJS 	= 	$(SRC:.c=.o)
CC 		= 	gcc
CFLAGS 	= 	-Wall -Werror -Wextra -fsanitize=thread -g
RM	 	= 	rm -rf

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	@$(RM) $(OBJS)

fclean:	clean
	@$(RM) $(NAME)		

re:	fclean all

.PHONY:	all clean fclean re