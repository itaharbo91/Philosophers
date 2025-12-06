/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:12:09 by itaharbo          #+#    #+#             */
/*   Updated: 2025/05/17 20:47:10 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>

typedef struct s_semaphores
{
	sem_t			*forks;
	sem_t			*print;
	sem_t			*simulation_end;
	sem_t			*meals;
	sem_t			*sem_check;
	sem_t			*start;
	sem_t			*sem_full;
}	t_semaphores;

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	long long		start_time;
	t_semaphores	*semaphores;
}	t_data;

typedef struct s_philo
{
	int				number;
	int				meals_eaten;
	long long		last_meal_time;
	t_data			*data;
	t_semaphores	*semaphores;
}	t_philo;

int			parse_arg(int ac, char **av, t_data *data);
int			init_semaphores(t_semaphores *sema, t_data *data);
int			init_philos(t_data *data, t_semaphores *sema, pid_t *pids);

int			philo_routine(t_philo *philo);
void		*monitor_death(void *arg);
void		action_log(t_philo *philos, char *action);

void		free_semaphores(t_semaphores *sema);
void		unlink_semaphores(void);
void		null_semaphores(t_semaphores *sema);

void		safe_sleep(long long time);
long long	get_time(void);
int			is_number(char c);
int			is_space(char c);
long long	valid_atoi(char *str);

#endif
