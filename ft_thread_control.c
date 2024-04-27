/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 08:48:23 by bmarek            #+#    #+#             */
/*   Updated: 2024/04/26 14:23:58 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

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
	else if (thread_error_status == EINVAL && operation_type == CREATE_MUTEX)
		error_exit("Failed to create thread:"
			"Invalid thread attributes specified.");
	else if (thread_error_status == EINVAL && (operation_type == JOIN_MUTEX
			|| operation_type == DETACH_MUTEX))
		error_exit("Failed to join/detach thread:"
			"Thread is not joinable.");
	else if (thread_error_status == ESRCH)
		error_exit("Failed to join/detach thread:"
			"No thread found matching the given ID.");
	else if (thread_error_status == EDEADLK)
		error_exit("Failed to join/detach thread:"
			"Deadlock detected or the specified thread is the calling thread.");
}

void	manage_thread_operation(pthread_t *thread_id,
		void *(*thread_entry_point)(void *),
		void *thread_data, t_mutex_operation operation_type)
{
	if (operation_type == CREATE_MUTEX)
		process_thread_operation(pthread_create(thread_id,
				NULL, thread_entry_point, thread_data), operation_type);
	else if (operation_type == JOIN_MUTEX)
		process_thread_operation(pthread_join(*thread_id, NULL),
			operation_type);
	else if (operation_type == DETACH_MUTEX)
		process_thread_operation(pthread_detach(*thread_id),
			operation_type);
	else
		error_exit("Invalid operation type for thread management:"
			"Please specify one of the following operations:"
			"<CREATE>, <JOIN>, or <DETACH>");
}
