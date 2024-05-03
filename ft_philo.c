/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:08:35 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/03 10:54:33 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

//The main function serves as the entry point of the program. It checks if the correct number of command-line arguments is provided, 
// handles the parsing of these arguments to initialize the dining table, starts the dinner simulation, and frees the memory allocated 
// for the dining table after the simulation ends. If an incorrect number of arguments is provided, it displays an error message.
int	main(int argc, char **argv)
{
	t_dining_table	dining_table;

	if (argc == 5 || argc == 6)
	{
		handle_philos_args(&dining_table, argv);
		init_dining_table(&dining_table);
		begin_dinner_simulation(&dining_table);
		free_dining_table(&dining_table);
	}
	else
		error_message();
}
