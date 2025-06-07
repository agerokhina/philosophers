/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:57:25 by aerokhin          #+#    #+#             */
/*   Updated: 2025/04/11 16:42:41 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philos *philo, int fork)
{
	pthread_mutex_lock(philo->forks[fork]);
	print_status(philo, "has taken a fork", &philo->env->print);
}

void	put_forks(t_philos *philo)
{
	pthread_mutex_unlock(philo->forks[FIRST_FORK]);
	pthread_mutex_unlock(philo->forks[SECOND_FORK]);
}
