/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dinner_status_checker.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 07:16:52 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/03 11:15:38 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"
#include <stdio.h>

// Check if a philosopher has died.
// This function checks if a philosopher has exceeded the time since their last meal,
// indicating a potential death due to starvation.
// Parameters:
// - philo: Pointer to the philosopher structure.
// Returns:
// - True if the philosopher has died, false otherwise.

static bool	philo_death_check(t_philo *philo)
{
	bool	is_full;
	long	time_since_last_meal;
	long	time_until_death;

	process_mutex_operation(&philo->philo_mutex_lock, LOCK_MUTEX);
	is_full = philo->ate_enough;
	process_mutex_operation(&philo->philo_mutex_lock, UNLOCK_MUTEX);
	process_mutex_operation(&philo->philo_mutex_lock, LOCK_MUTEX);
	time_since_last_meal = get_current_time(MILLISECOND)
		- philo->time_of_last_meal;
	process_mutex_operation(&philo->philo_mutex_lock, UNLOCK_MUTEX);
	time_until_death = philo->dining_table->time_until_philo_die / 1000;
	if (is_full)
		return (false);
	if (time_since_last_meal > time_until_death)
		return (true);
	return (false);
}

// Set a boolean variable with mutex locking.
// This function safely sets a boolean variable with proper mutex locking.
// Parameters:
// - mutex: Pointer to the mutex structure.
// - dest: Pointer to the boolean variable to be set.
// - value: Boolean value to set.

void	set_bool(t_mtx	*mutex, bool *dest, bool value)
{
	process_mutex_operation(mutex, LOCK_MUTEX);
	*dest = value;
	process_mutex_operation(mutex, UNLOCK_MUTEX);
}

// Check if the simulation has finished.
// This function checks if the dining simulation has finished.
// Parameters:
// - dining_table: Pointer to the dining table structure.
// Returns:
// - True if the simulation has finished, false otherwise.

bool	simulation_finished(t_dining_table *dining_table)
{
	bool	simulation_complete;

	process_mutex_operation(&dining_table->data_access_mutex, LOCK_MUTEX);
	simulation_complete = dining_table->end_simulation;
	process_mutex_operation(&dining_table->data_access_mutex, UNLOCK_MUTEX);
	return (simulation_complete);
}

// Observe the progress of the dinner simulation.
// This function continuously observes the progress of the dinner simulation,
// checking for philosopher deaths and updating the simulation status accordingly.
// Parameters:
// - dining_table_info: Pointer to the dining table structure.
// Returns:
// - NULL pointer.

void	*observe_dinner_progress(void *dining_table_info)
{
	int				i;
	t_dining_table	*dining_table;

	dining_table = (t_dining_table *)dining_table_info;
	while (!all_threads_running(&dining_table->data_access_mutex,
			&dining_table->current_thread_count, dining_table->num_of_philos))
		;
	while (!simulation_finished(dining_table))
	{
		i = 0;
		while (dining_table->num_of_philos > i
			&& !simulation_finished(dining_table))
		{
			if (philo_death_check(dining_table->philos + i))
			{
				set_bool(&dining_table->data_access_mutex,
					&dining_table->end_simulation, true);
				check_and_print_philo_status(PHILO_DIED,
					dining_table->philos + i);
			}
			i++;
		}
	}
	return (NULL);
}
