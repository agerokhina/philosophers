/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:19:23 by aerokhin          #+#    #+#             */
/*   Updated: 2025/05/15 16:19:54 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_time(t_philos *philo)
{
	time_t	time;

	time = philo->env->time_to_die - (get_time() - philo->last_time_eating);
	if (time >= philo->env->time_to_eat * 1.5)
	{
		ft_usleep(philo->env->time_to_eat, philo->env);
		return ;
	}
}

void	eating(t_philos *philo)
{
	if (is_dead(philo) == DEAD || is_full(philo))
		return ;
	pthread_mutex_lock(&philo->checks);
	philo->last_time_eating = get_time();
	print_status(philo, "is eating", &philo->env->print);
	pthread_mutex_unlock(&philo->checks);
	ft_usleep(philo->env->time_to_eat, philo->env);
	pthread_mutex_lock(&philo->checks);
	philo->meal_count -= (philo->env->meal_num != -1 && philo->meal_count > 0);
	pthread_mutex_unlock(&philo->checks);
}

void	sleeping(t_philos *philo)
{
	if (is_dead(philo) == DEAD || is_full(philo))
		return ;
	print_status(philo, "is sleeping", &philo->env->print);
	ft_usleep(philo->env->time_to_sleep, philo->env);
}

void	thinking(t_philos *philo)
{
	if (is_dead(philo) == DEAD || is_full(philo))
	{
		return ;
	}
	print_status(philo, "is thinking", &philo->env->print);
	usleep(CPU_PAUSE);
}

void	kill_all_philosophers(t_philos *philos, int philo_num)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philos[i].env->check_dead);
	philos->env->dead = DEAD;
	pthread_mutex_unlock(&philos[i].env->check_dead);
	pthread_mutex_lock(&philos[i].env->check_meal);
	philos->env->full = FULL;
	pthread_mutex_unlock(&philos[i].env->check_meal);
	while (i < philo_num)
	{
		pthread_mutex_lock(&philos[i].checks);
		philos[i].dead = DEAD;
		pthread_mutex_unlock(&philos[i].checks);
		i++;
	}
}
