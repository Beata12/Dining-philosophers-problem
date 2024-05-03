/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:06:55 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/03 10:53:01 by bmarek           ###   ########.fr       */
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

# ifndef PHILOS_LIMIT
#  define PHILOS_LIMIT 200
# endif

typedef enum e_philo_status
{
	PHILO_EATS,			 	// Philosopher is eating
	PHILO_SLEEPS,			// Philosopher is sleeping
	PHILO_THINKS,			// Philosopher is thinking
	TAKE_LEFT_FORK,		 	// Philosopher takes the left fork
	TAKE_RIGHT_FORK,		// Philosopher takes the right fork
	PHILO_DIED,			  	// Philosopher has died
}			t_philo_status;

typedef enum e_time_unit
{
	SECONDS,			// Time unit in seconds
	MILLISECOND,		// Time unit in milliseconds
	MICROSECOND,		// Time unit in microseconds
}		t_time_unit;

typedef enum e_mutex_operation
{
	CREATE_THREAD,		// Create a thread
	DETACH_THREAD,		// Detach a thread
	DESTROY_THREAD,		// Detach a thread
	INITIALIZE_MUTEX,   // Initialize a mutex
	JOIN_MUTEX,		 	// Join a mutex
	LOCK_MUTEX,		 	// Lock a mutex
	UNLOCK_MUTEX,	   	// Unlock a mutex
}			t_mutex_operation;

typedef struct s_dining_table	t_dining_table;
typedef pthread_mutex_t			t_mtx;

typedef struct s_fork
{
	t_mtx		fork;		 	// Mutex for the fork
	int			fork_id;	  	// Unique identifier for the fork
}				t_fork;


typedef struct s_philo
{
	bool			ate_enough;				// Flag indicating if philosopher has eaten enough meals
	int				philo_id;				// Unique identifier for the philosopher
	long			num_of_eaten_meals;   	// Number of meals eaten by the philosopher
	long			time_of_last_meal;		// Time of the last meal eaten by the philosopher
	pthread_t		thread_id;				// Thread identifier for the philosopher
	t_fork			*left_fork;		   		// Pointer to the left fork of the philosopher
	t_fork			*right_fork;		 	// Pointer to the right fork of the philosopher
	t_mtx			philo_mutex_lock;	 	// Mutex for locking access to philosopher's resources
	t_dining_table	*dining_table;			// Pointer to the dining table
}				t_philo;

struct	s_dining_table
{
	bool		end_simulation;				// Flag indicating if the simulation has ended
	bool		threads_availability;	   	// Flag indicating the availability of threads
	long		current_thread_count;	   	// Number of currently active threads
	long		max_num_of_meals;		   	// Maximum number of meals to be eaten
	long		num_of_philos;			  	// Number of philosophers
	long		sleep_time;				 	// Time for which a philosopher sleeps
	long		start_simulation;		   	// Time when the simulation starts
	long		time_until_philo_die;	   	// Time until a philosopher dies without eating
	long		time_to_finish_meal;		// Time needed to finish a meal
	pthread_t	monitor_thread_id;		  	// Thread identifier for the monitor thread
	t_fork		*forks;					 	// Array of forks
	t_mtx		data_access_mutex;		 	// Mutex for synchronizing data access
	t_mtx		print_operation_mutex;	  	// Mutex for synchronizing print operations
	t_philo		*philos;					// Array of philosophers
};

// Function prototypes for various functions defined in the code. 
bool	all_threads_running(t_mtx *mutex, long *thread,
			long philosopher_index);
bool	is_philo_full(t_philo *philo);
bool	is_simulation_finished(t_dining_table *dining_table);

long	get_current_time(int time_unit);

void	begin_dinner_simulation(t_dining_table *dining_table);
void	check_and_print_philo_status(t_philo_status philo_status,
			t_philo *philo);
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
void	manipulate_long(t_mtx *mutex, long *target_value, long update_value,
			bool increment_value);
void	my_usleep(long usec, t_dining_table *dining_table);
void	*observe_dinner_progress(void *dining_table_info);
void	perform_thinking_process(t_philo *philo, bool pre_simulation);
void	process_mutex_operation(t_mtx *mutex_handle,
			t_mutex_operation operation_type);
void	set_last_meal_time(t_philo *philo);
void	wait_for_all_threads_ready(t_dining_table *dining_table);

void	perform_eating(t_philo *philo);

#endif