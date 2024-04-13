/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:06:55 by bmarek            #+#    #+#             */
/*   Updated: 2024/04/13 12:47:28 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct Philosopher
{
    int num_of_philos;
    struct Fork *left_fork;
    struct Fork *right_fork;
    pthread_mutex_t mutex_philo;
} Philosopher;

typedef struct Fork
{
    int num_of_fork;
    pthread_mutex_t mutex_fork;
} Fork;

typedef struct Time
{
    int last_meal;
} Time;


int ft_atoi (char *str);

void	error_message(void);
void	error_input(void);

#endif