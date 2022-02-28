NAME	=	philo
CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror -g -pthread -g3 -fsanitize=address
SRC		=	philo.c

all: $(SRC)
	@ $(CC) $(FLAGS) $(SRC) -o $(NAME)
	@ echo "compilation OK"


clean:
	@rm -rf $(NAME)
	@ echo "clean done"

fclean: clean
	@rm -rf philo
	@ echo "fclean done"

re:
	rm -rf .o
	
.PHONY: all clean fclean re all