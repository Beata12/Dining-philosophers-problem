/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:06:55 by bmarek            #+#    #+#             */
/*   Updated: 2024/04/26 14:45:43 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H 
# define FT_PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# ifndef DEBUG_FLAG
#  define DEBUG_FLAG 0
# endif

# ifndef PHILOS_LIMIT
#  define PHILOS_LIMIT 200
# endif

typedef enum e_philo_status
{
	PHILO_EATS,
	PHILO_DIED,
	PHILO_SLEEPS,
	PHILO_THINKS,
	TAKE_LEFT_FORK,
	TAKE_RIGHT_FORK,
}			t_philo_status;

typedef enum e_mutex_operation
{
	CREATE_MUTEX,
	DETACH_MUTEX,
	DESTROY_MUTEX,
	INITIALIZE_MUTEX,
	JOIN_MUTEX,
	LOCK_MUTEX,
	UNLOCK_MUTEX,
}			t_mutex_operation;

typedef enum e_time_unit
{
	SECONDS,
	MILLISECOND,
	MICROSECOND,
}		t_time_unit;

typedef struct s_dining_table	t_dining_table;
typedef pthread_mutex_t			t_mtx;

typedef struct s_fork
{
	t_mtx		fork;
	int			fork_id;
}				t_fork;

typedef struct s_philo
{
	bool			ate_enough;
	int				philo_id;
	long			num_of_eaten_meals;
	long			time_of_last_meal;
	pthread_t		thread_id;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_mtx			philo_mutex_lock;//wskazuje, że ten mutex jest używany do blokowania dostępu 
									//do zasobów filozofa
	t_dining_table	*dining_table;
}				t_philo;

struct	s_dining_table
{
	bool		end_simulation;
	bool		threads_availability;
	long		current_thread_count;
	long		max_num_of_meals;
	long		num_of_philos;
	long		sleep_time;
	long		start_simulation;
	long		time_until_philo_die;
	long		time_to_finish_meal;
	pthread_t	monitor_thread_id;
	t_fork		*forks;
	t_mtx		data_access_mutex;
	t_mtx		print_operation_mutex;
	t_philo		*philos;
};

bool	all_threads_running(t_mtx *mutex, long *thread,
			long philosopher_index);
bool	is_philo_full(t_philo *philo);
bool	is_simulation_finished(t_dining_table *dining_table);

long	get_current_time(int time_unit);

void	begin_dinner_simulation(t_dining_table *dining_table);
void	check_and_print_philo_status(t_philo_status philo_status,
			t_philo *philo, bool debug_flag);
void	desynchronize_philos(t_philo *philo);
void	error_exit(const char *error);
void	error_message(void);
void	error_time(void);
void	free_dining_table(t_dining_table *dining_table);
void	handle_philos_args(t_dining_table *dining_table, char **argv);
void	increase_threads_running_nbr(t_dining_table *dining_table);
void	init_dining_table(t_dining_table *dining_table);
void	manage_thread_operation(pthread_t *thread_id,
			void *(*thread_entry_point)(void *),
			void *thread_data, t_mutex_operation operation_type);
void	manipulate_long(t_mtx *mutex, long *dest, long value, bool increase);
void	my_usleep(long usec, t_dining_table *dining_table);
void	*observe_dinner_progress(void *dining_table_info);
void	perform_thinking_process(t_philo *philo, bool pre_simulation);
void	process_mutex_operation(t_mtx *mutex_handle,
			t_mutex_operation operation_type);
void	set_last_meal_time(t_philo *philo);
void	wait_for_all_threads_ready(t_dining_table *dining_table);

// int		ft_atoi (char *str);
// void	*safe_memory_allocation(size_t allocation_size);
// void	error_message(void);

#endif