/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmarek <bmarek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:44:12 by bmarek            #+#    #+#             */
/*   Updated: 2024/05/03 10:58:45 by bmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

// Display an error message indicating incorrect command-line arguments.
// This function prints an error message in red color, along with an example
// of correct input format and a description of the correct input format.
// The correct input format is also displayed in green color.

void	error_message(void)
{
	const char	*error_msg;
	const char	*correct_input;
	const char	*example_input;

	error_msg = "\033[31m\n❗		❗		❗		E	R	R	O	R		"
		"❗		❗		❗\033[0m\n\n";
	example_input = "\033[32m\nCORRECT INPUT \033[1m\033[35m "
		"./philo\033[36m 5 800 200 200 4\033[0m";
	correct_input = "\033[32m\nCORRECT INPUT\033[1m\033[35m "
		"./philo\033[36m <number_of_philosophers> <time_to_die> <time_to_eat>"
		"<time_to_sleep> [number_of_times_each_philosopher_must_eat] \033[0m";
	printf("%s", error_msg);
	printf("%s\n", example_input);
	printf("%s\n", correct_input);
}

// Display an error message for invalid time values.
// This function prints an error message in red color indicating that
// the time values provided must be greater than 60 milliseconds.
// It terminates the program if such an error occurs.

void	error_time(void)
{
	printf("\033[31m\n❗ ❗ ❗	E R R O R	❗ ❗ ❗\033[0m\n\n");
	printf("🚨   \033[31m Time must be grater than 60ms\033[0m   🚨\n");
	exit(EXIT_FAILURE);
}

// Display a custom error message and terminate the program.
// This function prints the provided error message and terminates
// the program with EXIT_FAILURE status.
// Parameters:
// - error: The custom error message to be displayed.

void	error_exit(const char *error)
{
	printf("🚨 %s 🚨\n", error);
	exit(EXIT_FAILURE);
}
