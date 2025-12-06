/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:44:13 by itaharbo          #+#    #+#             */
/*   Updated: 2025/05/17 21:57:59 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <string.h>

static void	philo_setup(t_philo *philo, t_data *data, t_semaphores *sema, int i)
{
	memset(philo, 0, sizeof(t_philo));
	philo->number = i + 1;
	philo->meals_eaten = 0;
	philo->data = data;
	philo->semaphores = sema;
	philo->last_meal_time = data->start_time;
}

static void	philos_start(t_data *data, t_semaphores *sema)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		sem_post(sema->start);
		i++;
	}
}

static void	*monitor_meals(void *arg)
{
	t_data	*data;
	int		count;

	count = 0;
	data = (t_data *)arg;
	while (1)
	{
		sem_wait(data->semaphores->sem_full);
		count++;
		if (count == data->number_of_philosophers)
		{
			sem_post(data->semaphores->simulation_end);
			break ;
		}
		usleep(100);
	}
	return (NULL);
}

static void	meals_threads_init(t_data *data)
{
	pthread_t	meals;

	if (pthread_create(&meals, NULL, monitor_meals, data) != 0)
	{
		write(2, "[Error]: pthread_create failed!\n", 33);
		return ;
	}
	pthread_detach(meals);
}

int	init_philos(t_data *data, t_semaphores *sema, pid_t *pids)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (write(2, "[Error]: fork failed!\n", 22), 1);
		if (pids[i] == 0)
		{
			philo = malloc(sizeof(t_philo));
			if (!philo)
				return (write(2, "[Error]: malloc failed!\n", 24), 1);
			philo_setup(philo, data, sema, i);
			philo_routine(philo);
			return (free(philo), 0);
		}
		i++;
	}
	meals_threads_init(data);
	philos_start(data, sema);
	return (0);
}
