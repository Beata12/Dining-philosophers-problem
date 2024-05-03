/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:26:47 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/03 11:08:18 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

// Get the current time.
// This function retrieves the current time in the specified time unit.
// It uses the gettimeofday function to get the time.
// Parameters:
// - time_unit: The time unit in which to return the current time.
//   Possible values are MILLISECOND, MICROSECOND, and SECONDS.
// Returns:
// The current time in the specified time unit.

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

// Delay execution for a specified amount of time.
// This function delays execution for the specified time duration,
// considering the end of the simulation to avoid unnecessary delay.
// Parameters:
// - time_to_wait: The time duration to wait in microseconds.
// - dining_table: Pointer to the dining table structure.

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

// Free memory allocated for the dining table.
// This function frees the memory allocated for the dining table,
// including forks and philosophers, and destroys associated mutexes.
// Parameters:
// - dining_table: Pointer to the dining table structure.

void	free_dining_table(t_dining_table *dining_table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (dining_table->num_of_philos > i)
	{
		philo = dining_table->philos + i;
		process_mutex_operation(&philo->philo_mutex_lock, DESTROY_THREAD);
		i++;
	}
	process_mutex_operation(&dining_table->print_operation_mutex,
		DESTROY_THREAD);
	process_mutex_operation(&dining_table->data_access_mutex, DESTROY_THREAD);
	free(dining_table->forks);
	free(dining_table->philos);
}

// Desynchronize philosophers.
// This function introduces a delay to desynchronize philosophers' actions,
// ensuring they don't start eating simultaneously.
// Parameters:
// - philo: Pointer to the philosopher structure.

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

// Manipulate a long integer atomically.
// This function updates a long integer atomically, either incrementing its value
// or setting it to a specified value, while ensuring thread safety.
// Parameters:
// - mutex: Pointer to the mutex for synchronization.
// - target_value: Pointer to the target long integer variable to be manipulated.
// - update_value: The value to which the target_value should be updated.
// - increment_value: Boolean indicating whether to increment the target_value.

void	manipulate_long(t_mtx *mutex, long *target_value,
		long update_value, bool increment_value)
{
	process_mutex_operation(mutex, LOCK_MUTEX);
	if (increment_value)
		(*target_value)++;
	else
		*target_value = update_value;
	process_mutex_operation(mutex, UNLOCK_MUTEX);
}
