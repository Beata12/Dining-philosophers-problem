/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dining_simulation_init.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 08:03:46 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/03 11:00:23 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

// Set up the forks for a philosopher.
// This function determines the left and right forks for a philosopher
// based on the philosopher's index and the total number of philosophers.
// If the philosopher's ID is even, the left fork will be the one at its index,
// otherwise, the left fork will be the one at the next index.
// Parameters:
// - philo: Pointer to the philosopher structure.
// - fork: Array of fork structures.
// - philosopher_index: Index of the philosopher.

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

// Initialize the philosophers.
// This function initializes the philosopher structures in the dining table.
// It sets the philosopher ID, meal count, and mutexes.
// Additionally, it sets up the forks for each philosopher.
// Parameters:
// - dining_table: Pointer to the dining table structure.

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

// Safely allocate memory.
// This function allocates memory with error checking using the malloc function.
// If memory allocation fails, it displays an error message and terminates the program.
// Parameters:
// - allocation_size: Size of memory to be allocated.
// Returns:
// A pointer to the allocated memory.

void	*safe_memory_allocation(size_t allocation_size)
{
	void	*allocated_memory;

	allocated_memory = malloc(allocation_size);
	if (allocated_memory == NULL)
		error_exit("Failed to allocate memory using malloc function");
	return (allocated_memory);
}

// Initialize the dining table.
// This function initializes the dining table structure.
// It allocates memory for philosophers and forks, initializes mutexes,
// and sets up the philosophers with their respective forks.
// Parameters:
// - dining_table: Pointer to the dining table structure.

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
