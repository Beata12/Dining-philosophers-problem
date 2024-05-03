/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_philos_args.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:00:54 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/03 10:56:33 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"
#include <stdio.h>

// Convert a string to an integer.
// This function parses the input string to extract an integer value.
// It handles leading whitespaces, signs, and converts the string representation
// of digits into an integer value.
// Parameters:
// - str: The string to be converted to an integer.
// Returns:
// The integer value extracted from the input string.

int	ft_atoi(char *str)
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


// Handle command-line arguments to initialize the dining table.
// This function parses the command-line arguments and initializes the dining table
// with the provided parameters.
// Parameters:
// - dining_table: A pointer to the dining table structure to be initialized.
// - argv: An array of strings containing the command-line arguments.

void	handle_philos_args(t_dining_table *dining_table, char **argv)
{
	dining_table->num_of_philos = ft_atoi(argv[1]);
	if (dining_table->num_of_philos > PHILOS_LIMIT)
	{
		printf("The maximum number of philosophers allowed is %d\n",
			PHILOS_LIMIT);
		exit(1);
	}
	dining_table->time_until_philo_die = ft_atoi(argv[2]) * 1000;
	dining_table->time_to_finish_meal = ft_atoi(argv[3]) * 1000;
	dining_table->sleep_time = ft_atoi(argv[4]) * 1000;
	if (dining_table->time_until_philo_die < 60000
		|| dining_table->sleep_time < 60000
		|| dining_table->time_to_finish_meal < 60000)
		error_time();
	if (argv[5])
	{
		if (ft_atoi(argv[5]) < 0)
			error_exit("Number of philo should be a positive value.");
		dining_table->max_num_of_meals = ft_atoi(argv[5]);
	}
	else
		dining_table->max_num_of_meals = -1;
}
