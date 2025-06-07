/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:29:43 by aerokhin          #+#    #+#             */
/*   Updated: 2025/04/29 11:37:19 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_forks(pthread_mutex_t **forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_destroy(&(*forks)[i]);
		i++;
	}
	free(*forks);
}

void	ft_destroy_env(t_env *env)
{
	pthread_mutex_destroy(&env->print);
	pthread_mutex_destroy(&env->check_dead);
	pthread_mutex_destroy(&env->check_meal);
}

void	ft_destroy_threads(t_philos *philo, int philo_num, int destroy_n_join)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (philo[i].created && !destroy_n_join)
			pthread_join(philo[i].thread, NULL);
		pthread_mutex_destroy(&philo[i].checks);
		i++;
	}
	if (philo->env->monitor_created && !destroy_n_join)
		pthread_join(philo->env->monitor_thread, NULL);
	if (philo->env->meal_num != -1)
		if (philo->env->monitor_meal_created && !destroy_n_join)
			pthread_join(philo->env->monitor_meal_thread, NULL);
	free(philo);
}

int	destroy_all(t_env *env, t_destroys destroys, char *err_msg)
{
	if (destroys.destroy_forks)
	{
		if (destroys.destroy_philos == 1)
			ft_destroy_forks(&env->forks, env->philo_num);
		else
			ft_destroy_forks(&env->forks, destroys.philo_num);
	}
	if (destroys.destroy_philos)
		ft_destroy_threads(env->philos, destroys.philo_num, \
							destroys.destroy_n_join);
	if (destroys.destroy_env)
		ft_destroy_env(env);
	return (ft_return_error(err_msg));
}
