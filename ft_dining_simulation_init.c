/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dining_simulation_init.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 08:03:46 by bmarek            #+#    #+#             */
/*   Updated: 2024/04/26 16:27:02 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

static void	setup_forks_for_philosopher(t_philo *philo, t_fork *fork,
		int philosopher_index)
{
	int	philosopher_count;

	philosopher_count = philo->dining_table->num_of_philos;
	philo->left_fork = &fork[(philosopher_index + 1) % philosopher_count];
	philo->right_fork = &fork[philosopher_index];
	if (philo->philo_id % 2 == 0)
	{
		philo->left_fork = &fork[philosopher_index];
		philo->right_fork = &fork[(philosopher_index + 1) % philosopher_count];
	}
}

static void	initialize_philosophers(t_dining_table *dining_table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < dining_table->num_of_philos)
	{
		philo = dining_table->philos + i;
		philo->philo_id = i + 1;
		philo->ate_enough = false;
		philo->num_of_eaten_meals = 0;
		process_mutex_operation(&philo->philo_mutex_lock, INITIALIZE_MUTEX);
		philo->dining_table = dining_table;
		setup_forks_for_philosopher(philo, dining_table->forks, i);
		i++;
	}
}

void	*safe_memory_allocation(size_t allocation_size)
{
	void	*allocated_memory;

	allocated_memory = malloc(allocation_size);
	if (allocated_memory == NULL)
		error_exit("Failed to allocate memory using malloc function");
	return (allocated_memory);
}

void	init_dining_table(t_dining_table *dining_table)
{
	int		i;

	i = 0;
	dining_table->end_simulation = false;
	dining_table->threads_availability = false;
	dining_table->current_thread_count = 0;
	dining_table->philos = safe_memory_allocation(dining_table->num_of_philos
			* sizeof(t_philo));
	dining_table->forks = safe_memory_allocation(dining_table->num_of_philos
			* sizeof(t_fork));
	process_mutex_operation(&dining_table->print_operation_mutex,
		INITIALIZE_MUTEX);
	process_mutex_operation(&dining_table->data_access_mutex, INITIALIZE_MUTEX);
	while (i < dining_table->num_of_philos)
	{
		process_mutex_operation(&dining_table->forks[i].fork, INITIALIZE_MUTEX);
		dining_table->forks[i].fork_id = i;
		i++;
	}
	initialize_philosophers(dining_table);
}
