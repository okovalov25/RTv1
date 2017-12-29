#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okovalov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/23 15:48:21 by okovalov          #+#    #+#              #
#    Updated: 2017/08/28 12:54:32 by okovalov         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = RTv1

SRC = 	raytrace.c \
		normal.c \
		inter.c \
		key.c \
		matnlig.c \
		rot.c \
		vectors.c \

OBJ = $(SRC:.c=.o)

CC = gcc

FLGS = -Wall -Wextra -Werror

INC = ./

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) -o $(NAME) $(OBJ) -lmlx -framework OpenGL -framework AppKit

%.o: %.c
		$(CC) $(FLGS) -c $<

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all