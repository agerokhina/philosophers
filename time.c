/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:36:49 by aerokhin          #+#    #+#             */
/*   Updated: 2025/05/12 12:37:15 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void	ft_usleep(int time);
// void	ft_sleep(int time);
// void 	time_stamp(time_t start_time);

#include "philo.h"

time_t	time_since_start(time_t start_time)
{
	return (get_time() - start_time);
}

void	time_stamp(time_t start_time)
{
	printf("%ld ", time_since_start(start_time));
}

time_t	get_time(void)
{
	struct timeval	current_time;
	time_t			time;

	if (gettimeofday(&current_time, NULL) == -1)
	{
		perror("gettimeofday");
		exit(1);
	}
	time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time);
}

void	ft_usleep(int time, t_env *env)
{
	time_t	start_time;
	int		pause_time;

	start_time = get_time();
	pause_time = 100 + 5 * env->philo_num;
	while (time_since_start(start_time) < time && are_dead(env) != DEAD)
	{
		usleep(pause_time);
	}
}
