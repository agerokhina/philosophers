/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerokhin <aerokhin@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:49:31 by aerokhin          #+#    #+#             */
/*   Updated: 2025/05/12 13:39:30 by aerokhin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define CPU_PAUSE 1000
# define EAT 0
# define SLEEP 1
# define THINK 2
# define DEAD 3
# define FULL 4
# define FIRST_FORK 0
# define SECOND_FORK 1
# define TXT_RED "\x1b[31m"
# define TXT_GREEN "\x1b[32m"
# define TXT_YELLOW "\x1b[33m"
# define TXT_BLUE "\x1b[34m"
# define TXT_BOLD "\x1b[1m"
# define TXT_UNDERL "\x1b[4m"
# define TXT_ITAL "\x1b[3m"
# define TXT_RES "\x1b[0m"

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>

typedef struct s_env	t_env;
typedef struct s_philos	t_philos;

typedef struct s_philos
{
	int				philo_id;
	pthread_t		thread;
	time_t			last_time_eating;
	pthread_mutex_t	*forks[2];
	pthread_mutex_t	checks;
	int				dead;
	int				meal_count;
	t_env			*env;
	int				start_pause;
	int				created;
}					t_philos;

typedef struct s_env
{
	int				philo_num;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				meal_num;
	time_t			start_time;
	pthread_mutex_t	print;
	pthread_mutex_t	check_meal;
	pthread_mutex_t	check_dead;
	pthread_mutex_t	*forks;
	t_philos		*philos;
	pthread_t		monitor_thread;
	int				monitor_created;
	pthread_t		monitor_meal_thread;
	int				monitor_meal_created;
	int				dead;
	int				full;
}				t_env;	

typedef struct s_destroys
{
	int	philo_num;
	int	destroy_forks;
	int	destroy_philos;
	int	destroy_env;
	int	destroy_n_join;
}		t_destroys;

// threads functions
void	*thread_function(void *arg);
void	*monitor(void *arg);
void	*monitor_meal(void *arg);
void	run_solo_philosopher(t_philos *philo);

//activities
void	eating(t_philos *philo);
void	sleeping(t_philos *philo);
void	thinking(t_philos *philo);
int		dead(t_env *env, int i, time_t last_meal);
int		full_all(t_env *env, int full);
void	kill_all_philosophers(t_philos *philos, int philo_num);

// forks
void	take_fork(t_philos *philo, int fork);
void	put_forks(t_philos *philo);

// inits
int		init_env(t_env *env, int argc, char **argv);
int		init_forks(t_env *env);
int		init_philos(t_env *env, t_philos **philos, int philo_num, \
					pthread_mutex_t **forks);
int		init_threads(t_env *env);

// destroys
void	ft_destroy_env(t_env *env);
void	ft_destroy_threads(t_philos *philo, int philo_num, int destroy_n_join);
void	ft_destroy_forks(pthread_mutex_t **forks, int philo_num);
int		destroy_all(t_env *env, t_destroys destroys, char *err_msg);

// utils
int		ft_atoi(const char *str);
void	print_status(t_philos *philo, char *status, pthread_mutex_t *print);
int		ft_return_error(char *err_msg);

//prints
void	print_env(t_env *env);
void	print_philos(t_philos *philos, int philo_num);

// time
time_t	time_since_start(time_t start_time);
void	ft_usleep(int time, t_env *env);
void	time_stamp(time_t start_time);
time_t	get_time(void);
void	time_to_die(t_philos *philo);
void	check_time(t_philos *philo);

//validation
int		validate_input(int argc, char **argv);

//checks
int		are_full(t_env *env);
int		are_dead(t_env *env);
int		is_dead(t_philos *philo);
int		is_full(t_philos *philo);
size_t	ft_strlen(const char *str);
int		ft_all_digits(char *str);
#endif