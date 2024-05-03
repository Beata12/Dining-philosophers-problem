/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dinner_simulation_functions.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 07:16:04 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/03 11:11:16 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

// Set last meal time.
// This function updates the time of the last meal for a philosopher.
// It locks the philosopher's mutex to ensure atomicity and unlocks it afterward.
// Parameters:
// - philo: Pointer to the philosopher structure.

void	set_last_meal_time(t_philo *philo)
{
	process_mutex_operation(&philo->philo_mutex_lock, LOCK_MUTEX);
	philo->time_of_last_meal = get_current_time(MILLISECOND);
	process_mutex_operation(&philo->philo_mutex_lock, UNLOCK_MUTEX);
}

// Check if simulation is finished.
// This function checks if the simulation has finished by examining the end_simulation flag
// in the dining table structure.
// It locks the data access mutex to ensure synchronization and unlocks it afterward.
// Parameters:
// - dining_table: Pointer to the dining table structure.
// Returns:
// true if the simulation has finished, false otherwise.

bool	is_simulation_finished(t_dining_table *dining_table)
{
	bool	simulation_finished;

	process_mutex_operation(&dining_table->data_access_mutex, LOCK_MUTEX);
	simulation_finished = dining_table->end_simulation;
	process_mutex_operation(&dining_table->data_access_mutex, UNLOCK_MUTEX);
	return (simulation_finished);
}

// Check if philosopher is full.
// This function checks if a philosopher has eaten enough meals.
// It locks the philosopher's mutex to ensure atomicity and unlocks it afterward.
// Parameters:
// - philo: Pointer to the philosopher structure.
// Returns:
// true if the philosopher has eaten enough meals, false otherwise.

bool	is_philo_full(t_philo *philo)
{
	bool	philo_full;

	process_mutex_operation(&philo->philo_mutex_lock, LOCK_MUTEX);
	philo_full = philo->ate_enough;
	process_mutex_operation(&philo->philo_mutex_lock, UNLOCK_MUTEX);
	return (philo_full);
}
