/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_performance_of_the_process.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 11:16:04 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/03 11:12:43 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

// Perform the thinking process for a philosopher.
// This function simulates the thinking process for a philosopher.
// It calculates the duration of thinking time based on eating and sleeping times.
// If pre_simulation is false, it also prints the philosopher's thinking status.
// Parameters:
// - philo: Pointer to the philosopher structure.
// - pre_simulation: Boolean indicating whether this is before the simulation starts.

void	perform_thinking_process(t_philo *philo, bool pre_simulation)
{
	long	eating_time;
	long	sleeping_time;
	long	thinking_time;

	if (!pre_simulation)
		check_and_print_philo_status(PHILO_THINKS, philo);
	if (philo->dining_table->num_of_philos % 2 == 0)
		return ;
	eating_time = philo->dining_table->time_to_finish_meal;
	sleeping_time = philo->dining_table->sleep_time;
	thinking_time = (eating_time * 2) - sleeping_time;
	if (thinking_time < 0)
		thinking_time = 0;
	my_usleep(thinking_time * 0.42, philo->dining_table);
}

// Perform the eating process for a philosopher.
// This function simulates the eating process for a philosopher.
// It locks both the left and right forks, updates the time of the last meal,
// and increments the number of eaten meals.
// If the maximum number of meals is set and reached, it marks the philosopher
// as having eaten enough.
// Parameters:
// - philo: Pointer to the philosopher structure.

void	perform_eating(t_philo *philo)
{
	process_mutex_operation(&philo->left_fork->fork, LOCK_MUTEX);
	check_and_print_philo_status(TAKE_LEFT_FORK, philo);
	process_mutex_operation(&philo->right_fork->fork, LOCK_MUTEX);
	check_and_print_philo_status(TAKE_RIGHT_FORK, philo);
	process_mutex_operation(&philo->philo_mutex_lock, LOCK_MUTEX);
	philo->time_of_last_meal = get_current_time(MILLISECOND);
	process_mutex_operation(&philo->philo_mutex_lock, UNLOCK_MUTEX);
	philo->num_of_eaten_meals++;
	check_and_print_philo_status(PHILO_EATS, philo);
	my_usleep(philo->dining_table->time_to_finish_meal, philo->dining_table);
	if (philo->dining_table->max_num_of_meals > 0
		&& philo->num_of_eaten_meals == philo->dining_table->max_num_of_meals)
	{
		process_mutex_operation(&philo->philo_mutex_lock, LOCK_MUTEX);
		philo->ate_enough = true;
		process_mutex_operation(&philo->philo_mutex_lock, UNLOCK_MUTEX);
	}
	process_mutex_operation(&philo->left_fork->fork, UNLOCK_MUTEX);
	process_mutex_operation(&philo->right_fork->fork, UNLOCK_MUTEX);
}
