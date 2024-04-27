# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 08:21:21 by bmarek            #+#    #+#              #
#    Updated: 2024/04/26 16:17:52 by bmarek           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -O2
 
MAKE_LIB = ar -rcs

SRCS = ft_main.c \
	   ft_dinner_simulation_functions.c \
	   ft_dining_philosophers.c \
	   ft_dining_simulation_init.c \
	   ft_dinner_status_checker.c \
       ft_error_handling.c \
	   ft_handle_philos_args.c \
	   ft_mutex_control.c \
	   ft_philo_utils.c \
	   ft_philosopher_dining_simulation.c \
	   ft_thread_control.c \

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
	make title
	@curl 'http://141.148.244.146:8080/ansi?start=7e22ce&end=e11d48&padding=10&text=42PHILOS'

$(OBJS) : $(SRCS)
	$(CC) $(CFLAGS) -c $^ 

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all title

text:
	@curl 'http://141.148.244.146:8080/ansi?start=7e22ce&end=e11d48&padding=10&text=42PHILOS'

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
