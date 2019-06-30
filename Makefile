# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbrochar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/15 17:13:45 by sbrochar          #+#    #+#              #
#    Updated: 2019/06/30 12:36:16 by rhealitt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ant

INC_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj

LIB_DIR = ./lib/libft
LIBFT = $(LIB_DIR)/libft.a

SRC = vmain.c \
	rooms.c \
	links.c \
	paths.c \
	solution.c \
	collisions.c \
	collisions_2.c \
	lock.c \
	migration.c \
	validation.c \
	parse_rooms.c \
	parse_lins.c

OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

CC = gcc
CFLAGS = -g -c -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIB_DIR) `sdl2-config --cflags`
LFLAGS = -L$(LIB_DIR) -lft `sdl2-config --libs` -lSDL2_gfx -lSDL2_ttf -lm

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@printf "%-54c\rLinking...\n" ' '
	@$(CC) -o $@ $^ $(LFLAGS)
	@printf "Done !\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ $^
	@printf "Compiling... %-21s => %-21s\r" $^ $@

$(LIBFT):
	make -C $(LIB_DIR)

clean:
	@make -C $(LIB_DIR) clean
	@rm -f $(OBJ)
	@printf "Removed objs\n"

fclean: clean
	@make -C $(LIB_DIR) fclean
	@rm -f $(NAME)
	@printf "Removed $(NAME)\n"

re: fclean all

.PHONY: all clean fclean re
