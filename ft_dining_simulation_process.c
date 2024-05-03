/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dining_simulation_process.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 11:16:04 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/03 11:18:14 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

// ** Check the simulation status.
// ** This function continuously checks if the simulation has ended.
// ** It waits until the end_simulation flag is set to true in the dining table.
// ** Parameters:
// ** - philo: Pointer to the philosopher structure.

void	check_simulation_status(t_philo *philo)
{
	bool	end_simulation;

	while (true)
	{
		end_simulation = false;
		process_mutex_operation(&philo->dining_table->data_access_mutex,
			LOCK_MUTEX);
		end_simulation = philo->dining_table->end_simulation;
		process_mutex_operation(&philo->dining_table->data_access_mutex,
			UNLOCK_MUTEX);
		if (end_simulation)
			break ;
		my_usleep(200, philo->dining_table);
	}
}

// ** Handle a single philosopher's actions.
// ** This function represents the behavior of a single philosopher during the dinner.
// ** It waits until all threads are ready, updates the philosopher's last meal time,
// ** increases the count of running threads, and performs necessary actions.
// ** Parameters:
// ** - arg: Pointer to the philosopher structure.
// ** Returns:
// ** NULL pointer.

static void	*handle_single_philosopher(void *arg)
{
	t_philo			*philo;
	t_dining_table	*dining_table;
	bool			are_all_threads_ready;

	philo = (t_philo *)arg;
	dining_table = philo->dining_table;
	are_all_threads_ready = false;
	while (!are_all_threads_ready)
	{
		process_mutex_operation(&dining_table->data_access_mutex, LOCK_MUTEX);
		are_all_threads_ready = dining_table->threads_availability;
		process_mutex_operation(&dining_table->data_access_mutex, UNLOCK_MUTEX);
	}
	manipulate_long(&philo->philo_mutex_lock, &philo->time_of_last_meal,
		get_current_time(MILLISECOND), false);
	manipulate_long(&dining_table->data_access_mutex,
		&dining_table->current_thread_count, 1, true);
	check_and_print_philo_status(TAKE_LEFT_FORK, philo);
	check_simulation_status(philo);
	return (NULL);
}

// ** Perform the dinner simulation for a philosopher.
// ** This function represents the dining process for a philosopher.
// ** It waits until all threads are ready, sets the last meal time for the philosopher,
// ** increases the count of running threads, and simulates the dinner process.
// ** Parameters:
// ** - philosopher_data: Pointer to the philosopher structure.
// ** Returns:
// ** NULL pointer.

static void	*perform_dinner_simulation(void *philosopher_data)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher_data;
	wait_for_all_threads_ready(philo->dining_table);
	set_last_meal_time(philo);
	increase_threads_running_nbr(philo->dining_table);
	desynchronize_philos(philo);
	while (true)
	{
		if (is_simulation_finished(philo->dining_table))
			break ;
		if (is_philo_full(philo))
			break ;
		perform_eating(philo);
		check_and_print_philo_status(PHILO_SLEEPS, philo);
		my_usleep(philo->dining_table->sleep_time, philo->dining_table);
		perform_thinking_process(philo, false);
	}
	return (NULL);
}

// ** Run the dinner operations.
// ** This function starts the dinner operations for all philosophers.
// ** It creates threads to handle each philosopher's dinner simulation process.
// ** Parameters:
// ** - dining_table: Pointer to the dining table structure.

void	run_dinner_operations(t_dining_table *dining_table)
{
	int	i;

	i = 0;
	if (dining_table->max_num_of_meals == 0)
		return ;
	else if (dining_table->num_of_philos == 1)
		manage_thread_operation(&dining_table->philos[0].thread_id,
			handle_single_philosopher, &dining_table->philos[0], CREATE_THREAD);
	else
	{
		while (dining_table->num_of_philos > i)
		{
			manage_thread_operation(&dining_table->philos[i].thread_id,
				perform_dinner_simulation, &dining_table->philos[i],
				CREATE_THREAD);
			i++;
		}
	}
}

// ** Begin the dinner simulation.
// ** This function initiates the dinner simulation process.
// ** It starts threads to handle the dinner operations, including the monitor thread,
// ** and ensures synchronization between threads.
// ** Parameters:
// ** - dining_table: Pointer to the dining table structure.

void	begin_dinner_simulation(t_dining_table *dining_table)
{
	int	i;

	i = 0;
	run_dinner_operations(dining_table);
	manage_thread_operation(&dining_table->monitor_thread_id,
		observe_dinner_progress, dining_table, CREATE_THREAD);
	dining_table->start_simulation = get_current_time(MILLISECOND);
	process_mutex_operation(&dining_table->data_access_mutex, LOCK_MUTEX);
	dining_table->threads_availability = true;
	process_mutex_operation(&dining_table->data_access_mutex, UNLOCK_MUTEX);
	while (dining_table->num_of_philos > i)
	{
		manage_thread_operation(&dining_table->philos[i].thread_id, NULL, NULL,
			JOIN_MUTEX);
		i++;
	}
	process_mutex_operation(&dining_table->data_access_mutex, LOCK_MUTEX);
	dining_table->end_simulation = true;
	process_mutex_operation(&dining_table->data_access_mutex, UNLOCK_MUTEX);
	manage_thread_operation(&dining_table->monitor_thread_id, NULL, NULL,
		JOIN_MUTEX);
}
