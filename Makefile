# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/07 18:35:25 by ecorreia          #+#    #+#              #
#    Updated: 2022/04/07 18:37:19 by ecorreia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
CC		=	gcc
RM		=	rm -rf
FLAGS	=	-Wall -Wextra -Werror -g -pthread -g3 -fsanitize=address
INCLUDE =	inc/philo.h
SRC		=	src/main.c		\
			src/philo.c		\
			src/actions.c	\
			src/utils.c

all: $(SRC)
	@ $(CC) $(FLAGS) $(SRC) -o $(NAME)
	@ echo "compilation OK"

linux: $(SRC)
	@ $(CC) $(FLAGS) $(INCLUDE) $(SRC) -o $(NAME)
	@ echo "compilation OK"

clean:
	@$(RM) $(NAME)
	@ echo "clean done"

fclean: clean
	@$(RM) philo
	@ echo "fclean done"

re: clean all
	
.PHONY: all clean fclean re