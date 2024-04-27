/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 08:35:51 by bmarek            #+#    #+#             */
/*   Updated: 2024/04/26 16:28:36 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

static void	process_mutex_error(int status, t_mutex_operation operation_type)
{
	if (0 == status)
		return ;
	if (status == EBUSY)
		error_exit("Mutex is busy:"
			"Another thread or process is currently using the mutex,"
			"so it can't be locked right now.");
	else if (status == EDEADLK)
		error_exit("Deadlock detected:"
			"A deadlock would occur if the thread blocked waiting for mutex.");
	else if (status == EINVAL && operation_type == INITIALIZE_MUTEX)
		error_exit("Invalid attribute value:"
			"Specified attribute value for mutex initialization is invalid.");
	else if (status == EINVAL && (operation_type == LOCK_MUTEX
			|| operation_type == UNLOCK_MUTEX))
		error_exit("Invalid operation:"
			"Attempted to lock or unlock an invalid mutex.");
	else if (status == ENOMEM)
		error_exit("Memory allocation failed:"
			"The process cannot allocate enough memory"
			"to create another mutex.");
	else if (status == EPERM)
		error_exit("Operation not permitted:"
			"The current thread does not hold a lock on the mutex.");
}

void	process_mutex_operation(t_mtx *mutex_handle,
		t_mutex_operation operation_type)
{
	if (operation_type == LOCK_MUTEX)
		process_mutex_error(pthread_mutex_lock(mutex_handle),
			operation_type);
	else if (operation_type == UNLOCK_MUTEX)
		process_mutex_error(pthread_mutex_unlock(mutex_handle),
			operation_type);
	else if (operation_type == INITIALIZE_MUTEX)
		process_mutex_error(pthread_mutex_init(mutex_handle, NULL),
			operation_type);
	else if (operation_type == DESTROY_MUTEX)
		process_mutex_error(pthread_mutex_destroy(mutex_handle),
			operation_type);
	else
		error_exit("Invalid operation type for mutex handling."
			"Please use one of the following operations:"
			"<LOCK>, <UNLOCK>, <INIT>, <DESTROY>.");
}
