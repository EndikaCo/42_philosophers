# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecorreia <ecorreia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/07 18:35:25 by ecorreia          #+#    #+#              #
#    Updated: 2022/04/08 19:28:07 by ecorreia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = clang
FLAGS = -Werror -Wextra -Wall
RM = rm -rf
FILES = src/main \
		src/philo \
		src/actions \
		src/utils
		
SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addsuffix .o, $(FILES))

all: $(NAME)

.c.o: $(FILES)
	@$(CC) $(FLAGS) -c -o $@ $<

$(NAME): $(OBJS) $(SRC)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo compilado ok

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re