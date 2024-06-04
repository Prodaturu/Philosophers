# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 17:41:46 by sprodatu          #+#    #+#              #
#    Updated: 2024/06/05 00:08:31 by sprodatu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.silent: all clean fclean re

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c syntax_check.c struct_init.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
