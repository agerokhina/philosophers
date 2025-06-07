/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:29:46 by aerokhin          #+#    #+#             */
/*   Updated: 2025/06/07 17:19:05 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_env(t_env *env, int argc, char **argv)
{
	env->philo_num = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env->meal_num = ft_atoi(argv[5]);
	else
		env->meal_num = -1;
	env->start_time = get_time();
	env->dead = 0;
	env->full = 0;
	if (!(pthread_mutex_init(&env->print, NULL) == 0))
		return (ft_return_error("Mutex init (print) failed\n"));
	if (!(pthread_mutex_init(&env->check_meal, NULL) == 0))
	{
		pthread_mutex_destroy(&env->print);
		return (ft_return_error("Error: mutex init (check_meal) failed\n"));
	}
	if (!(pthread_mutex_init(&env->check_dead, NULL) == 0))
	{
		pthread_mutex_destroy(&env->print);
		pthread_mutex_destroy(&env->check_meal);
		return (ft_return_error("Mutex init (check_meal) failed\n"));
	}
	return (0);
}

int	init_forks(t_env *env)
{
	int	i;

	i = 0;
	env->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
					* env->philo_num);
	if (!(env->forks))
		return (destroy_all(env, (t_destroys){0, 0, 0, 1, 0}, \
			TXT_RED "Error: malloc (forks) failed\n" TXT_RES));
	while (i < env->philo_num)
	{
		if (pthread_mutex_init(&(env->forks)[i], NULL) != 0)
			return (destroy_all(env, (t_destroys){i, 1, 0, 1, 0}, \
				TXT_RED "Error: mutex init (forks) failed\n" TXT_RES));
		i++;
	}
	return (0);
}

void	init_philo_values(t_philos *philos, int i, t_env *env)
{
	philos[i].philo_id = i + 1;
	philos[i].last_time_eating = get_time();
	philos[i].dead = 0;
	philos[i].meal_count = env->meal_num;
	philos[i].env = env;
}

int	init_philos(t_env *env, t_philos **philos, int philo_num, \
					pthread_mutex_t **forks)
{
	int	i;

	i = -1;
	*philos = (t_philos *)malloc(sizeof(t_philos) * philo_num);
	if (!(*philos))
		return (destroy_all(env, (t_destroys){philo_num, 1, 0, 1, 0}, \
			TXT_RED "Error: malloc failed for philos\n" TXT_RES));
	while (++i < philo_num)
	{
		init_philo_values(*philos, i, env);
		(*philos)[i].forks[(i % 2 + 1) % 2] = &(*forks)[i];
		(*philos)[i].forks[i % 2] = &(*forks)[(i + 1) % philo_num];
		if (!(pthread_mutex_init(&(*philos)[i].checks, NULL) == 0))
			return (destroy_all(env, (t_destroys){i, 1, 1, 1, 0}, \
				TXT_RED "Error: mutex init (checks) failed\n" TXT_RES));
		(*philos)[i].start_pause = env->time_to_eat * (i % 2) / 2 * CPU_PAUSE;
	}
	env->philos = *philos;
	// (*philos)[--i].forks[0] = &(*forks)[0];
	// (*philos)[i].forks[1] = &(*forks)[(i) % philo_num];
	return (0);
}

int	init_threads(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->philo_num)
	{
		env->philos[i].created = (pthread_create(&env->philos[i].thread, \
			NULL, thread_function, &env->philos[i]) == 0);
		if (!env->philos[i].created)
			return (destroy_all(env, (t_destroys){i, 1, 1, 1, 0},
				TXT_RED "Error: thread creation failed\n" TXT_RES));
	}
	env->monitor_created = (pthread_create(&env->monitor_thread, \
		NULL, monitor, env) == 0);
	if (!env->monitor_created)
		return (destroy_all(env, (t_destroys){env->philo_num, 1, 1, 1, 0}, \
				TXT_RED "Error: thread (monitor) creation failed\n" TXT_RES));
	if (env->meal_num != -1)
	{
		env->monitor_meal_created = (pthread_create(&env->monitor_meal_thread, \
			NULL, monitor_meal, env) == 0);
		if (!env->monitor_meal_created)
			return (destroy_all(env, (t_destroys){env->philo_num, 1, 1, 1, 0}, \
			TXT_RED "Error: thread (monitor_meal) creation failed\n" TXT_RES));
	}
	return (0);
}
