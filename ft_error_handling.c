/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:44:12 by bmarek            #+#    #+#             */
/*   Updated: 2024/04/13 12:44:01 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	error_message(void)
{
	const char	*error_msg;
	const char *correct_input;

	error_msg = "\033[31m\n❗		❗		❗		E	R	R	O	R		❗		❗		❗\033[0m\n\n";
	correct_input = "\033[32m\n CORRECT INPUT\033[1m\033[35m ./philo\033[36m <number_of_philosophers> <time_to_die time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat] \033[0m";

	printf("%s", error_msg);
	printf("%s\n", correct_input);
}

void	error_input(void)
{
	const char	*error_msg;
	const char *correct_input;

	error_msg = "\033[31m\n❗	❗	❗	E	R	R	O	R	❗	❗	❗\033[0m\n\n";
	correct_input = "\033[32m\n		CORRECT INPUT\033[1m\033[35m ./philo\033[36m <4> <200> <200> [7] \033[0m";

	printf("%s", error_msg);
	printf("%s\n", correct_input);
}