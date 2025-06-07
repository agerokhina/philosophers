/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:30:15 by aerokhin          #+#    #+#             */
/*   Updated: 2025/05/15 17:10:48 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_function(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->env->philo_num == 1)
	{
		run_solo_philosopher(philo);
		return (NULL);
	}
	usleep(philo->start_pause);
	philo->start_pause = 0;
	while (is_dead(philo) != DEAD && !is_full(philo))
	{
		check_time(philo);
		take_fork(philo, FIRST_FORK);
		take_fork(philo, SECOND_FORK);
		eating(philo);
		put_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_env	*env;
	int		i;
	time_t	last_meal;
	int		fl;

	env = (t_env *)arg;
	while (are_dead(env) != DEAD && are_full(env) != FULL)
	{
		i = -1;
		fl = are_dead(env) != DEAD && are_full(env) != FULL;
		while (++i < env->philo_num && fl)
		{
			pthread_mutex_lock(&env->philos[i].checks);
			last_meal = env->philos[i].last_time_eating;
			pthread_mutex_unlock(&env->philos[i].checks);
			if (get_time() - last_meal > env->time_to_die)
			{
				print_status(&env->philos[i], "died", &env->print);
				kill_all_philosophers(env->philos, env->philo_num);
				return (NULL);
			}
		}
		usleep(CPU_PAUSE);
	}
	return (NULL);
}

void	*monitor_meal(void *arg)
{
	t_env	*env;
	int		i;
	int		full;
	int		fl;

	env = (t_env *)arg;
	fl = are_dead(env) != DEAD && are_full(env) != FULL;
	while (fl && env->philo_num > 1)
	{
		i = 0;
		full = 0;
		while (i < env->philo_num && are_full(env) != FULL)
			full += is_full(&env->philos[i++]);
		if (full == env->philo_num)
		{
			pthread_mutex_lock(&env->check_meal);
			env->full = FULL;
			pthread_mutex_unlock(&env->check_meal);
			return (NULL);
		}
		usleep(CPU_PAUSE);
		fl = are_dead(env) != DEAD && are_full(env) != FULL;
	}
	return (NULL);
}

void	run_solo_philosopher(t_philos *philo)
{
	pthread_mutex_lock(philo->forks[0]);
	print_status(philo, "has taken a fork", &philo->env->print);
	ft_usleep(philo->env->time_to_die, philo->env);
	print_status(philo, "died", &philo->env->print);
	pthread_mutex_unlock(philo->forks[0]);
	pthread_mutex_lock(&philo->env->check_dead);
	philo->env->dead = DEAD;
	pthread_mutex_unlock(&philo->env->check_dead);
	pthread_mutex_lock(&philo->checks);
	philo->dead = DEAD;
	pthread_mutex_unlock(&philo->checks);
}
