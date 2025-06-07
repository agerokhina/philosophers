CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -flto -O3 -g  -fsanitize=thread
NAME = philo
SOURCE_FILES = 	./philo.c \
				./init.c \
				./utils.c \
				./time.c \
				./forks.c \
				./checks.c \
				./threads.c \
				./destroys.c \
				./activities.c \
				./validations.c \

OBJECT_FILES = $(SOURCE_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT_FILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECT_FILES) 

clean:
	rm -f $(OBJECT_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean all fclean re
