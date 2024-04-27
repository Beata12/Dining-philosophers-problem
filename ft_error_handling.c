/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:44:12 by bmarek            #+#    #+#             */
/*   Updated: 2024/04/26 14:57:47 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	error_message(void)
{
	const char	*error_msg;
	const char	*correct_input;
	const char	*example_input;

	error_msg = "\033[31m\n❗		❗		❗		E	R	R	O	R		"
		"❗		❗		❗\033[0m\n\n";
	example_input = "\033[32m\nCORRECT INPUT \033[1m\033[35m "
		"./philo\033[36m 5 800 200 200 4\033[0m";
	correct_input = "\033[32m\nCORRECT INPUT\033[1m\033[35m "
		"./philo\033[36m <number_of_philosophers> <time_to_die> <time_to_eat>"
		"<time_to_sleep> [number_of_times_each_philosopher_must_eat] \033[0m";
	printf("%s", error_msg);
	printf("%s\n", example_input);
	printf("%s\n", correct_input);
}

void	error_time(void)
{
	printf("\033[31m\n❗ ❗ ❗	E R R O R	❗ ❗ ❗\033[0m\n\n");
	printf("🚨   \033[31m Time must be grater than 60ms\033[0m   🚨\n");
	exit(EXIT_FAILURE);
}

void	error_exit(const char *error)
{
	printf("🚨 %s 🚨\n", error);
	exit(EXIT_FAILURE);
}

// void	error_message(void)
// {
// 	printf("🚨 \033[31m\n❗ ❗ ❗	E R R O R	❗ ❗ ❗\033[0m\n\n 🚨\n");
// 	exit(EXIT_FAILURE);
// }
