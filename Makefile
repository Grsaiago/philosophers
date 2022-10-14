# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/12 16:43:03 by gsaiago           #+#    #+#              #
#    Updated: 2022/10/14 16:02:29 by gsaiago          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc -pthread

CFLAGS = -g

SRCS = $(wildcard *.c)

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(NAME)
	rm -rf $(NAME).dSYM

re: clean all

fclean: clean

val: $(NAME)
	valgrind ./$(NAME) 2

.PHONY: all clean re fclean
