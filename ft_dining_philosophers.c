/* *************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dining_philosophers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 08:22:29 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/03 11:09:14 by bmarek           ###   ########.fr       */
/*                                                                            */
/* *************************************************************************/

#include "ft_philo.h"

// Print philosopher status.
// This function prints the status of a philosopher based on the current situation.
// It displays different messages depending on the philosopher's status and whether
// the simulation has ended.
// Parameters:
// - philo_status: The status of the philosopher.
// - time_since_last_meal: Time passed since the philosopher's last meal.
// - philo_id: The ID of the philosopher.
// - end_simulation: Boolean indicating whether the simulation has ended.

static void	print_philo_status(t_philo_status philo_status,
	long time_since_last_meal, int philo_id, bool end_simulation)
{
	if ((philo_status == TAKE_LEFT_FORK || philo_status == TAKE_RIGHT_FORK)
		&& !end_simulation)
		printf("%-6ld %d   🍽	has taken a fork  🍽\n", time_since_last_meal, philo_id);
	else if (philo_status == PHILO_EATS && !end_simulation)
		printf("%-6ld %d   🍝	is eating	  🍝 \n", time_since_last_meal, philo_id);
	else if (philo_status == PHILO_SLEEPS && !end_simulation)
		printf("%-6ld %d   😴	is sleeping	  😴\n", time_since_last_meal, philo_id);
	else if (philo_status == PHILO_THINKS && !end_simulation)
		printf("%-6ld %d   🤔	is thinking	  🤔\n", time_since_last_meal, philo_id);
	else if (philo_status == PHILO_DIED)
		printf("%-6ld %d 💀💀💀 died 		💀💀💀\n", time_since_last_meal, philo_id);
}

// Check and print philosopher status.
// This function checks the philosopher's status, calculates the time since the last meal,
// and prints the corresponding status message if the philosopher has not eaten enough.
// Parameters:
// - philo_status: The status of the philosopher.
// - philo: Pointer to the philosopher structure.

void	check_and_print_philo_status(t_philo_status philo_status,
								t_philo *philo)
{
	long	time_since_last_meal;
	bool	is_full;
	bool	end_simulation;

	process_mutex_operation(&philo->philo_mutex_lock, LOCK_MUTEX);
	process_mutex_operation(&philo->philo_mutex_lock, UNLOCK_MUTEX);
	is_full = philo->ate_enough;
	if (is_full)
		return ;
	time_since_last_meal = get_current_time(MILLISECOND)
		- philo->dining_table->start_simulation;
	process_mutex_operation(&philo->dining_table->print_operation_mutex,
		LOCK_MUTEX);
	end_simulation = philo->dining_table->end_simulation;
	print_philo_status(philo_status, time_since_last_meal, philo->philo_id,
		end_simulation);
	process_mutex_operation(&philo->dining_table->print_operation_mutex,
		UNLOCK_MUTEX);
}
