/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 08:48:23 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/03 11:06:32 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

// ** Check if all threads are running.
// ** This function checks if the specified thread is currently running.
// ** It locks the mutex to access the thread status and unlocks it afterward.
// ** Parameters:
// ** - mutex: Pointer to the mutex for thread status synchronization.
// ** - thread: Pointer to the variable representing the current thread index.
// ** - philosopher_index: The index of the philosopher thread to be checked.
// ** Returns:
// ** true if the specified thread is running, false otherwise.

bool	all_threads_running(t_mtx *mutex, long *thread,
		long philosopher_index)
{
	bool	threads_status;

	threads_status = false;
	process_mutex_operation(mutex, LOCK_MUTEX);
	if (*thread == philosopher_index)
		threads_status = true;
	process_mutex_operation(mutex, UNLOCK_MUTEX);
	return (threads_status);
}

// ** Wait for all threads to be ready.
// ** This function waits until all threads are ready to start execution.
// ** It locks the mutex to access the threads availability status.
// ** Parameters:
// ** - dining_table: Pointer to the dining table structure.

void	wait_for_all_threads_ready(t_dining_table *dining_table)
{
	bool	all_threads_ready;

	while (true)
	{
		process_mutex_operation(&dining_table->data_access_mutex, LOCK_MUTEX);
		all_threads_ready = dining_table->threads_availability;
		process_mutex_operation(&dining_table->data_access_mutex, UNLOCK_MUTEX);
		if (all_threads_ready)
			break ;
	}
}

// ** Process thread operation.
// ** This function handles errors that may occur during thread operations.
// ** It checks the error status returned by pthread functions and displays
// ** an appropriate error message.
// ** Parameters:
// ** - thread_error_status: The error status returned by pthread functions.
// ** - operation_type: The type of thread operation being performed.

static void	process_thread_operation(int thread_error_status,
									t_mutex_operation operation_type)
{
	if (thread_error_status == 0)
		return ;
	if (thread_error_status == EAGAIN)
		error_exit("Failed to create thread:"
			"Insufficient resources available.");
	else if (thread_error_status == EPERM)
		error_exit("Failed to create thread:"
			"Permission denied.");
	else if (thread_error_status == EINVAL && operation_type == CREATE_THREAD)
		error_exit("Failed to create thread:"
			"Invalid thread attributes specified.");
	else if (thread_error_status == EINVAL && (operation_type == JOIN_MUTEX
			|| operation_type == DETACH_THREAD))
		error_exit("Failed to join/detach thread:"
			"Thread is not joinable.");
	else if (thread_error_status == ESRCH)
		error_exit("Failed to join/detach thread:"
			"No thread found matching the given ID.");
	else if (thread_error_status == EDEADLK)
		error_exit("Failed to join/detach thread:"
			"Deadlock detected or the specified thread is the calling thread.");
}

// ** Manage thread operation.
// ** This function manages thread operations such as thread creation, joining,
// ** and detachment.
// ** It handles error checking for each operation using process_thread_operation function.
// ** Parameters:
// ** - thread_id: Pointer to the thread ID.
// ** - thread_entry_point: Pointer to the function representing the thread's entry point.
// ** - thread_data: Pointer to the data to be passed to the thread.
// ** - operation_type: The type of thread operation to be performed.

void	manage_thread_operation(pthread_t *thread_id,
		void *(*thread_entry_point)(void *),
		void *thread_data, t_mutex_operation operation_type)
{
	if (operation_type == CREATE_THREAD)
		process_thread_operation(pthread_create(thread_id,
				NULL, thread_entry_point, thread_data), operation_type);
	else if (operation_type == JOIN_MUTEX)
		process_thread_operation(pthread_join(*thread_id, NULL),
			operation_type);
	else if (operation_type == DETACH_THREAD)
		process_thread_operation(pthread_detach(*thread_id),
			operation_type);
	else
		error_exit("Invalid operation type for thread management:"
			"Please specify one of the following operations:"
			"<CREATE>, <JOIN>, or <DETACH>");
}

// ** Increase the count of running threads.
// ** This function increments the count of currently running threads in the dining table.
// ** It locks the mutex to access the thread count and unlocks it afterward.
// ** Parameters:
// ** - dining_table: Pointer to the dining table structure.

void	increase_threads_running_nbr(t_dining_table *dining_table)
{
	process_mutex_operation(&dining_table->data_access_mutex, LOCK_MUTEX);
	dining_table->current_thread_count++;
	process_mutex_operation(&dining_table->data_access_mutex, UNLOCK_MUTEX);
}
