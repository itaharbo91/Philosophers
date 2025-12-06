/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:47:41 by itaharbo          #+#    #+#             */
/*   Updated: 2025/05/07 15:01:37 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	last_meal(t_philo *philos, t_data *data)
{
	long long		since_last_meal;
	struct timeval	time_now;
	struct timeval	last_meal_copy;

	pthread_mutex_lock(&philos->philo_mutex);
	last_meal_copy = philos->last_meal_time;
	pthread_mutex_unlock(&philos->philo_mutex);
	gettimeofday(&time_now, NULL);
	since_last_meal = (time_now.tv_sec - last_meal_copy.tv_sec) * 1000
		+ (time_now.tv_usec - last_meal_copy.tv_usec) / 1000;
	pthread_mutex_lock(&data->start_mutex);
	if (since_last_meal > data->time_to_die)
	{
		if (data->simulation_status == ENDED)
		{
			pthread_mutex_unlock(&data->start_mutex);
			return ;
		}
		data->simulation_status = ENDED;
		action_log(philos, "died");
	}
	pthread_mutex_unlock(&data->start_mutex);
}

static int	nb_philos_must_eat(t_philo *philos)
{
	int	i;

	i = 0;
	philos->data->philos_full = 0;
	while (i < philos->data->number_of_philosophers)
	{
		pthread_mutex_lock(&philos[i].philo_mutex);
		if (philos[i].times_eaten
			== philos->data->number_of_times_each_philosopher_must_eat)
			philos->data->philos_full++;
		pthread_mutex_unlock(&philos[i].philo_mutex);
		i++;
	}
	if (philos->data->philos_full == philos->data->number_of_philosophers)
	{
		pthread_mutex_lock(&philos->data->start_mutex);
		if (philos->data->simulation_status == STARTED)
			philos->data->simulation_status = ENDED;
		pthread_mutex_unlock(&philos->data->start_mutex);
		return (1);
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)arg;
	start_status(philos);
	while (1)
	{
		if (end_status(philos))
			break ;
		i = 0;
		while (i < philos->data->number_of_philosophers)
		{
			if (end_status(philos))
				break ;
			last_meal(&philos[i], philos->data);
			if (end_status(philos))
				break ;
			if (philos->data->number_of_times_each_philosopher_must_eat != -1)
				if (nb_philos_must_eat(philos) == 1)
					break ;
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
