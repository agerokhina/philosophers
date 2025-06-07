/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:03:54 by aerokhin          #+#    #+#             */
/*   Updated: 2025/04/29 12:46:57 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_env	env;
	int		i;

	if (validate_input(argc, argv))
		return (1);
	if (init_env(&env, argc, argv))
		return (1);
	if (init_forks(&env))
		return (1);
	if (init_philos(&env, &env.philos, env.philo_num, &env.forks))
		return (1);
	if (init_threads(&env))
		return (1);
	i = -1;
	while (++i < env.philo_num)
		pthread_join(env.philos[i].thread, NULL);
	if (pthread_join(env.monitor_thread, NULL) != 0)
		return (destroy_all(&env, (t_destroys){env.philo_num, 1, 1, 1, 0}, \
				TXT_RED "Error: join failed for monitor_thread\n" TXT_RES));
	if (env.meal_num != -1)
		if (pthread_join(env.monitor_meal_thread, NULL) != 0)
			return (destroy_all(&env, (t_destroys){env.philo_num, 1, 1, 1, 0}, \
			TXT_RED "Error: join failed for monitor_meal_thread\n" TXT_RES));
	destroy_all(&env, (t_destroys){env.philo_num, 1, 1, 1, 1}, "");
}
