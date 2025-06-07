/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:04:35 by aerokhin          #+#    #+#             */
/*   Updated: 2025/05/15 16:19:45 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	are_full(t_env *env)
{
	int	res;

	pthread_mutex_lock(&env->check_meal);
	res = env->full;
	pthread_mutex_unlock(&env->check_meal);
	return (res);
}

int	are_dead(t_env *env)
{
	int	res;

	pthread_mutex_lock(&env->check_dead);
	res = env->dead;
	pthread_mutex_unlock(&env->check_dead);
	return (res);
}

int	is_dead(t_philos *philo)
{
	int	res;

	pthread_mutex_lock(&philo->checks);
	res = philo->dead;
	pthread_mutex_unlock(&philo->checks);
	return (res);
}

int	is_full(t_philos *philo)
{
	int	res;

	pthread_mutex_lock(&philo->checks);
	res = philo->meal_count;
	pthread_mutex_unlock(&philo->checks);
	return (res == 0);
}
