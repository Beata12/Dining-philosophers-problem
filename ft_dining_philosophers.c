/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dining_philosophers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 08:22:29 by bmarek            #+#    #+#             */
/*   Updated: 2024/04/26 15:07:47 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"
#include <time.h>

static void	write_status_debug(t_philo_status philo_status, t_philo *philo,
		long elapsed)
{
	bool	end_simulation;

	end_simulation = false;
	process_mutex_operation(&philo->dining_table->data_access_mutex,
		LOCK_MUTEX);
	end_simulation = philo->dining_table->end_simulation;
	if (philo_status == TAKE_LEFT_FORK && !end_simulation)
		printf("%6ld %d has taken the 1° fork 🍽 \t\t\tn°[🍴 %d 🍴]\n",
			elapsed, philo->philo_id, philo->left_fork->fork_id);
	else if (philo_status == TAKE_RIGHT_FORK && !end_simulation)
		printf("%6ld %d has taken the 2° fork 🍽 \t\t\tn°[🍴 %d 🍴]\n",
			elapsed, philo->philo_id, philo->right_fork->fork_id);
	else if (philo_status == PHILO_EATS && !end_simulation)
		printf("%6ld %d is eating 🍝 \t\t\t[🍝 %ld 🍝]\n",
			elapsed, philo->philo_id, philo->num_of_eaten_meals);
	else if (philo_status == PHILO_SLEEPS && !end_simulation)
		printf("%6ld %d is sleeping 😴\n", elapsed, philo->philo_id);
	else if (philo_status == PHILO_THINKS && !end_simulation)
		printf("%6ld %d is thinking 🤔\n", elapsed, philo->philo_id);
	else if (philo_status == PHILO_DIED)
		printf("\t\t💀💀💀 %6ld %d died   💀💀💀\n", elapsed,
			philo->philo_id);
	process_mutex_operation(&philo->dining_table->data_access_mutex,
		UNLOCK_MUTEX);
}

void	check_and_print_philo_status(t_philo_status philo_status,
		t_philo *philo, bool debug_flag)
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
	if (debug_flag)
		write_status_debug(philo_status, philo, time_since_last_meal);
	else
	{
		if ((philo_status == TAKE_LEFT_FORK || philo_status == TAKE_RIGHT_FORK)
			&& !end_simulation)
			printf("%-6ld %d has taken a fork\n", time_since_last_meal,
				philo->philo_id);
		else if (philo_status == PHILO_EATS && !end_simulation)
			printf("%-6ld %d is eating\n", time_since_last_meal,
				philo->philo_id);
		else if (philo_status == PHILO_SLEEPS && !end_simulation)
			printf("%-6ld %d is sleeping\n", time_since_last_meal,
				philo->philo_id);
		else if (philo_status == PHILO_THINKS && !end_simulation)
			printf("%-6ld %d is thinking\n", time_since_last_meal,
				philo->philo_id);
		else if (philo_status == PHILO_DIED)
			printf("%-6ld %d died\n", time_since_last_meal, philo->philo_id);
	}
	process_mutex_operation(&philo->dining_table->print_operation_mutex,
		UNLOCK_MUTEX);
}
