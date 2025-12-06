/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:10:43 by itaharbo          #+#    #+#             */
/*   Updated: 2025/04/29 16:14:24 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef enum e_status
{
	NOT_STARTED = 0,
	STARTED = 1,
	ENDED = -1,
}	t_status;

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				philos_full;
	t_status		simulation_status;
	long long		timestamp;
	struct timeval	time_start;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks_mutex;
}	t_data;

typedef struct s_philo
{
	int				number;
	int				times_eaten;
	struct timeval	last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	philo_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

int			parse_arg(int ac, char **av, t_data *data);
int			philos_creation(t_data *data, t_philo **philos);
int			mutex_creation(t_data *data, t_philo *philos);
int			philos_pthread_creation(t_philo *philos, t_data *data);
int			thread_monitor(t_philo *philos, t_data *data,
				pthread_t *angel_of_death);
int			pthread_joining(t_philo *philos, t_data *data,
				pthread_t angel_of_death);

void		start_status(t_philo *philo);
int			end_status(t_philo *philo);
void		simulation_start(t_data *data, t_philo *philos);

void		*routine(void *arg);
void		is_eating(t_philo *philo);
void		*monitoring(void *arg);
void		action_log(t_philo *philos, char *action);
void		safe_sleep(long long time, t_philo *philos);

void		free_pthread(t_philo *philos, int number_of_philos);
void		*free_forks(t_data *data);
void		*free_philos(t_philo *philos);
void		*free_data(t_data *data);

long long	get_time(void);
int			is_number(char c);
int			is_space(char c);
long long	valid_atoi(char *str);

#endif
