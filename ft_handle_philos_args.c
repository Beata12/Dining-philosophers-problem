/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_philos_args.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:00:54 by bmarek            #+#    #+#             */
/*   Updated: 2024/04/26 14:56:02 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"
#include <stdio.h>

static int	ft_atoi(char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	if (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}

void	handle_philos_args(t_dining_table *dining_table, char **argv)
{
	dining_table->num_of_philos = ft_atoi(argv[1]);
	if (dining_table->num_of_philos > PHILOS_LIMIT)
	{
		printf("The maximum number of philosophers allowed is %d\n",
			PHILOS_LIMIT);
		exit(EXIT_FAILURE);
	}
	dining_table->time_until_philo_die = ft_atoi(argv[2]) * 1000;
	dining_table->time_to_finish_meal = ft_atoi(argv[3]) * 1000;
	dining_table->sleep_time = ft_atoi(argv[4]) * 1000;
	if (dining_table->time_until_philo_die < 60000
		|| dining_table->sleep_time < 60000
		|| dining_table->time_to_finish_meal < 60000)
		error_time();
	if (argv[5])
		dining_table->max_num_of_meals = ft_atoi(argv[5]);
	else
		dining_table->max_num_of_meals = -1;
}
