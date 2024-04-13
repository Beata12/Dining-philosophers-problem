/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:08:35 by bmarek            #+#    #+#             */
/*   Updated: 2024/04/13 12:55:01 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc == 5)
	{
		if (ft_atoi(argv[1]) && ft_atoi(argv[2]) && ft_atoi(argv[3]) && ft_atoi(argv[4]))
        {
            printf("%s\n", "Correct input");
        }
        else
            error_input();
	}
	else
	{
		error_message();
	}
}
