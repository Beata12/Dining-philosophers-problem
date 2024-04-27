/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:08:35 by bmarek            #+#    #+#             */
/*   Updated: 2024/04/26 14:54:01 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

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
