# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ple-thie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/20 23:39:38 by ple-thie          #+#    #+#              #
#    Updated: 2019/08/20 17:20:36 by asalazar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bsq

CC_FLAGS = gcc -Werror -Wall -Wextra

SRC = main.c con_file.c

OBF = main.o con_file.o

HEADER = ft.h

.PHONY: all
all: $(NAME)

$(NAME):
	$(CC_FLAGS) $(SRC) -c -I$(HEADER)
	gcc -o  $(NAME) $(OBF) -L. -lft

.PHONY: clean
clean:
	rm -f grid.txt grid1.txt
	rm -f $(OBF)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all

.PHONY: run
run: fclean all grid
	./bsq grid.txt grid1.txt
	cat grid.txt | ./bsq

.PHONY: grid
grid:
	perl generate_grid.pl 9 9 3 > grid.txt
	perl generate_grid.pl 15 15 5 > grid1.txt
