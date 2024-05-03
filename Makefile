# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 08:21:21 by bmarek            #+#    #+#              #
#    Updated: 2024/05/03 11:31:56 by bmarek           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -O2
#  CFLAGS += -fsanitize=thread 

MAKE_LIB = ar -rcs

SRCS = ft_philo.c \
	   ft_dining_simulation_process.c \
	   ft_dinner_simulation_functions.c \
       ft_error_handling.c \
	   ft_handle_philos_args.c \
	   ft_dining_simulation_init.c \
	   ft_mutex_control.c \
	   ft_philo_utils.c \
	   ft_dinner_status_checker.c \
	   ft_thread_control.c \
	   ft_dining_philosophers.c \
	   ft_performance_of_the_process.c \

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
	make title
	@curl 'http://141.148.244.146:8080/ansi?start=3cc322&end=fdbb2d&padding=5&text=DINNING_PHILOS'

$(OBJS) : $(SRCS)
	$(CC) $(CFLAGS) -c $^ 

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all title

.PHONY: all clean fclean re title

COLOR_GREEN=\033[32m
COLOR_YELLOW=\033[33m
COLOR_MAGENTA=\033[35m
COLOR_RED=\033[31m
COLOR_BLUE=\033[34m
COLOR_CYAN=\033[36m
BOLD=\033[1m
COLOR_END=\033[0m

title: 
	@clear
	@echo " "
	@echo " "
	@echo "$(COLOR_GREEN)$(BOLD)########   ##     ##  ##  ##         ######       #######        ######     ########   ##     ##  #########  ########     #######"
	@echo "##     ##  ##     ##  ##  ##        ##    ##     ##     ##      ##    ##    ##     ##  ##     ##  ##         ##     ##   ##     ##"
	@echo "##     ##  ##     ##  ##  ##       ##      ##   ##             ##      ##   ##     ##  ##     ##  ##         ##     ##  ##"
	@echo "##     ##  ##     ##  ##  ##      ##        ##   ##           ##        ##  ##     ##  ##     ##  ##         ##     ##   ##"
	@echo "########   #########  ##  ##      ##        ##    ########    ##        ##  ########   #########  #########  ########     ########"
	@echo "##         ##     ##  ##  ##      ##        ##           ##   ##        ##  ##         ##     ##  ##         ##  ##              ##"
	@echo "##         ##     ##  ##  ##       ##      ##             ##   ##      ##   ##         ##     ##  ##         ##   ##              ##"
	@echo "##         ##     ##  ##  ##        ##    ##     ##      ##     ##    ##    ##         ##     ##  ##         ##    ##    ##      ##"
	@echo "##         ##     ##  ##  ########   ######       #######        ######     ##         ##     ##  #########  ##     ##    #######"
	@echo "$(COLOR_YELLOW)"
	@echo ""
	@echo ""
	@echo "                                                                 🧠"
	@echo "                                                   ------------------------------ "                             
	@echo "                                                  |              🍛              |"
	@echo "                                                  |                              |"
	@echo "                                                  |       🥄            🥄       |"
	@echo "                                                  |                              |"
	@echo "                                               🧠 |  🍛                      🍛  | 🧠"
	@echo "                                                  |                              |"
	@echo "                                                  |       🥄            🥄       |"
	@echo "                                                  |                              |"
	@echo "                                                  |              🍛              |"
	@echo "                                                   ------------------------------ "                               
	@echo "                                                                 🧠"
	@echo ""
