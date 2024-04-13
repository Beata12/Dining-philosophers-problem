# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 08:21:21 by bmarek            #+#    #+#              #
#    Updated: 2024/04/13 12:54:10 by bmarek           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -O2
 
MAKE_LIB = ar -rcs

SRCS = ft_philo.c \
       ft_error_handling.c \
	   ft_philo_utils.c \

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
	make title

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
	