/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:30:03 by aerokhin          #+#    #+#             */
/*   Updated: 2025/05/12 13:41:19 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
	{
		i++;
	}
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int				i;
	unsigned int	res;
	int				str_len;
	int				sign;

	i = 0;
	res = 0;
	sign = 1;
	str_len = ft_strlen(nptr);
	while ((nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13)) \
			&& (i < str_len))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (i < str_len && nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return ((sign * (int)res));
}

void	print_status(t_philos *philo, char *status, pthread_mutex_t *print)
{
	pthread_mutex_lock(print);
	if (are_dead(philo->env) == DEAD || are_full(philo->env) == FULL)
	{
		pthread_mutex_unlock(print);
		return ;
	}
	time_stamp(philo->env->start_time);
	printf("%d %s\n", philo->philo_id, status);
	pthread_mutex_unlock(print);
}

int	ft_return_error(char *err_msg)
{
	ssize_t	ret;

	ret = write(1, err_msg, ft_strlen(err_msg));
	(void)ret;
	return (EXIT_FAILURE);
}

int	ft_all_digits(char *str)
{
	int	i;
	int	str_len;

	i = 0;
	str_len = ft_strlen(str);
	while (i < str_len)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
