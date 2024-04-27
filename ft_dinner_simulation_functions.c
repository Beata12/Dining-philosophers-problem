/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dinner_simulation_functions.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 07:16:04 by bmarek            #+#    #+#             */
/*   Updated: 2024/04/26 15:02:10 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

// Funkcja ustawiająca czas ostatniego posiłku
void	set_last_meal_time(t_philo *philo)
{
	process_mutex_operation(&philo->philo_mutex_lock, LOCK_MUTEX);
	philo->time_of_last_meal = get_current_time(MILLISECOND);
	process_mutex_operation(&philo->philo_mutex_lock, UNLOCK_MUTEX);
}

// Funkcja zwiększająca liczbę wątków
void	increase_threads_running_nbr(t_dining_table *dining_table)
{
	process_mutex_operation(&dining_table->data_access_mutex, LOCK_MUTEX);
	dining_table->current_thread_count++;
	process_mutex_operation(&dining_table->data_access_mutex, UNLOCK_MUTEX);
}

// Funkcja sprawdzająca, czy symulacja zakończona
bool	is_simulation_finished(t_dining_table *dining_table)
{
	bool	simulation_finished;

	process_mutex_operation(&dining_table->data_access_mutex, LOCK_MUTEX);
	simulation_finished = dining_table->end_simulation;
	process_mutex_operation(&dining_table->data_access_mutex, UNLOCK_MUTEX);
	return (simulation_finished);
}

// Funkcja sprawdzająca, czy filozof zjadł już maksymalną liczbę posiłków
bool	is_philo_full(t_philo *philo)
{
	bool	philo_full;

	process_mutex_operation(&philo->philo_mutex_lock, LOCK_MUTEX);
	philo_full = philo->ate_enough;
	process_mutex_operation(&philo->philo_mutex_lock, UNLOCK_MUTEX);
	return (philo_full);
}
