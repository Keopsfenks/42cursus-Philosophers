SRCS = ./srcs/mandatory_part/main.c \
		./srcs/mandatory_part/utils.c \
		./srcs/mandatory_part/list_functions.c \
		./srcs/mandatory_part/philo_life.c
		
NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\n"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[32mBuild successfull !\033[0m"

%.o: %.c
	@printf "\033[33mGenerating Philosophers objects... %-33.33s\r" $@
	@${CC} ${CFLAGS} -c $< -o $@


clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)
		
re:	fclean all


.PHONY: all re clean fclean