/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:29:39 by aerokhin          #+#    #+#             */
/*   Updated: 2025/05/12 13:40:37 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int		validate_input(int argc, char **argv);

#include "philo.h"

int	validate_input(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (ft_return_error(\
					TXT_RED "Error: wrong number of arguments\n" \
					TXT_RES "To run use:\n" \
					"./philo number_of_philosophers time_to_die "\
					"time_to_eat time_to_sleep [number_of_meals]\n"));
	i = 1;
	while (i < 5)
	{
		if (ft_atoi(argv[i]) <= 0 || ft_strlen(argv[i]) > 10 || \
					!ft_all_digits(argv[i]))
			return (ft_return_error(\
				TXT_RED "Error: incorrect argument\n" TXT_RES));
		i++;
	}
	if (argc == 6 && (ft_atoi(argv[5]) <= 0 || ft_strlen(argv[i]) > 10 || \
						!ft_all_digits(argv[5])))
		return (ft_return_error(\
				TXT_RED "Error: incorrect argument\n" TXT_RES));
	return (0);
}
