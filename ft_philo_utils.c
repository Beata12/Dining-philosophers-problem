/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:26:47 by bmarek            #+#    #+#             */
/*   Updated: 2024/04/26 15:10:56 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

long	get_current_time(int time_unit)
{
	struct timeval	time_value;

	if (gettimeofday(&time_value, NULL))
		error_exit("Failed to get the time: The gettimeofday function failed");
	if (time_unit == MILLISECOND)
		return (time_value.tv_sec * 1000 + time_value.tv_usec / 1000);
	else if (time_unit == MICROSECOND)
		return (time_value.tv_sec * 1000000 + time_value.tv_usec);
	else if (time_unit == SECONDS)
		return (time_value.tv_sec + time_value.tv_usec / 1000000);
	else
		error_exit("Invalid input for gettime: Please specify:"
			"use either <MILLISECOND>, <MICROSECOND>, or <SECONDS>.");
	return (0);
}

void	my_usleep(long time_to_wait, t_dining_table *dining_table)
{
	long	time_passed;
	long	remaining_time;
	long	beginning_timestamp;
	bool	end_of_simulation;

	beginning_timestamp = get_current_time(MICROSECOND);
	while (time_to_wait > get_current_time(MICROSECOND) - beginning_timestamp)
	{
		process_mutex_operation(&dining_table->data_access_mutex, LOCK_MUTEX);
		end_of_simulation = dining_table->end_simulation;
		process_mutex_operation(&dining_table->data_access_mutex, UNLOCK_MUTEX);
		if (end_of_simulation)
			break ;
		time_passed = get_current_time(MICROSECOND) - beginning_timestamp;
		remaining_time = time_to_wait - time_passed;
		if (remaining_time > 1000)
			usleep(remaining_time / 2);
		else
			while (time_to_wait > get_current_time(MICROSECOND)
				- beginning_timestamp)
				;
	}
}

void	free_dining_table(t_dining_table *dining_table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (dining_table->num_of_philos > i)
	{
		philo = dining_table->philos + i;
		process_mutex_operation(&philo->philo_mutex_lock, DESTROY_MUTEX);
		i++;
	}
	process_mutex_operation(&dining_table->print_operation_mutex,
		DESTROY_MUTEX);
	process_mutex_operation(&dining_table->data_access_mutex, DESTROY_MUTEX);
	free(dining_table->forks);
	free(dining_table->philos);
}

void	desynchronize_philos(t_philo *philo)
{
	if (philo->dining_table->num_of_philos % 2 == 0)
	{
		if (philo->philo_id % 2 == 0)
			my_usleep(3e4, philo->dining_table);
	}
	else
	{
		if (philo->philo_id % 2)
			perform_thinking_process(philo, true);
	}
}

void	manipulate_long(t_mtx *mutex, long *dest, long value, bool increase)
{
	process_mutex_operation(mutex, LOCK_MUTEX);
	if (increase)
		(*dest)++;
	else
		*dest = value;
	process_mutex_operation(mutex, UNLOCK_MUTEX);
}
