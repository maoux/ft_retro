# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arobion <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/25 11:07:50 by arobion           #+#    #+#              #
#    Updated: 2019/03/31 19:20:26 by arobion          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_retro
CC = clang++
CFLAGS = -Wall -Werror -Wextra -g3

INCLUDES_DIR = ./header/

SRCS_DIR = ./srcs/
OBJS_DIR = ./objs/

SRCS_FILES = main.cpp Map.cpp APhysicalEntity.cpp Monster.cpp Player.cpp Asteroid.cpp Boss.cpp EntityList.cpp Shot.cpp
OBJS_FILES = $(SRCS_FILES:.cpp=.o)

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_FILES))


all: $(NAME)

$(NAME) : $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) -lncurses -I$(INCLUDES_DIR) -o $(NAME) $(OBJS)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.cpp
	$(CC) $(CFLAGS) -o $@ -c $< -I$(INCLUDES_DIR)

clean: 
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all




.PHONY: all clean fclean re
