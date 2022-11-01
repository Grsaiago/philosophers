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
