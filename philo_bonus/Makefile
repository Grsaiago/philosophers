# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/02 20:10:02 by gsaiago           #+#    #+#              #
#    Updated: 2022/11/03 21:23:44 by gsaiago          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS =	ph_main_bonus.c \
		ph_validate_bonus.c \
		ph_dinner_bonus.c \
		ph_vulture_bonus.c \
		ph_utils_bonus.c \
		ph_atol_bonus.c \
		ph_exit_bonus.c \

CC = cc -pthread

CFLAGS = -g -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(NAME)
	rm -rf $(NAME).dSYM

fclean: clean

re: clean all

.PHONY:
	all re clean fclean 
