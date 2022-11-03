# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/02 20:10:02 by gsaiago           #+#    #+#              #
#    Updated: 2022/11/02 20:10:03 by gsaiago          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS = $(wildcard *.c)

CC = cc -pthread

CFLAGS = -g

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(NAME)
	rm -rf $(NAME).dSYM

re: clean all

t: re
	./$(NAME)	

.PHONY:
	all clean re t
