/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dinner_status_checker.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 07:16:52 by bmarek            #+#    #+#             */
/*   Updated: 2024/04/26 15:00:47 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"
#include <stdio.h>

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

void	*observe_dinner_progress(void *dining_table_info)
{
	int				i;
	t_dining_table	*dining_table;

	dining_table = (t_dining_table *)dining_table_info;
	while (!all_threads_running(&dining_table->data_access_mutex,
			&dining_table->current_thread_count, dining_table->num_of_philos));
	while (!dining_table->end_simulation)
	{
		i = 0;
		while (dining_table->num_of_philos > i && !dining_table->end_simulation)
		{
			if (philo_death_check(dining_table->philos + i))
			{
				process_mutex_operation(&dining_table->data_access_mutex,
					LOCK_MUTEX);
				dining_table->end_simulation = true;
				process_mutex_operation(&dining_table->data_access_mutex,
					UNLOCK_MUTEX);
				check_and_print_philo_status(PHILO_DIED,
					dining_table->philos + i, DEBUG_FLAG);
			}
			i++;
		}
	}
	return (NULL);
}
