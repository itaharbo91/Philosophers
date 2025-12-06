/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:05:08 by itaharbo          #+#    #+#             */
/*   Updated: 2025/05/17 21:54:59 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	alone_philo(t_philo *philo)
{
	start_status(philo);
	pthread_mutex_lock(philo->left_fork);
	action_log(philo, "has taken a fork");
	usleep(philo->data->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
}

static int	sleep_and_think(t_philo *philos)
{
	int	diff;

	if (end_status(philos))
		return (1);
	action_log(philos, "is sleeping");
	if (end_status(philos))
		return (1);
	safe_sleep(philos->data->time_to_sleep, philos);
	if (end_status(philos))
		return (1);
	action_log(philos, "is thinking");
	diff = (philos->data->time_to_eat - philos->data->time_to_sleep);
	if (diff > 0)
		usleep(diff * 2000);
	else
		usleep(2000);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->number_of_philosophers == 1)
		return (alone_philo(philo), NULL);
	if (philo->number % 2 != 0)
		usleep(2000);
	start_status(philo);
	while (!end_status(philo))
	{
		is_eating(philo);
		if (sleep_and_think(philo) == 1)
			break ;
	}
	return (NULL);
}
