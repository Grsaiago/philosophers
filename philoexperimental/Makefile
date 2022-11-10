# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/12 16:43:03 by gsaiago           #+#    #+#              #
#    Updated: 2022/11/10 19:22:08 by gsaiago          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc -pthread

CFLAGS =  -g -Wall -Wextra -Werror

SRCS =	ph_main.c \
		ph_utils.c \
		ph_atol.c \
		ph_validate.c \
		ph_vulture.c \
		ph_initialize.c \
		ph_dinner.c \
		ph_think_eat_sleep.c \
		ph_exit.c \


COLOR_GREEN=\033[0;32m
COLOR_RED=\033[0;31m
COLOR_BLUE=\033[0;34m
COLOR_END=\033[0m

all: $(NAME)

$(NAME): $(SRCS)
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
	@echo "$(COLOR_GREEN)Philosophers ready$(COLOR_END)"

clean:
	@rm -f $(NAME)
	@rm -rf $(NAME).dSYM
	@echo "$(COLOR_GREEN)Everything is clean$(COLOR_END)"

re: clean all

fclean: clean

.PHONY: all clean fclean re
