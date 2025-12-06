/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:51:32 by itaharbo          #+#    #+#             */
/*   Updated: 2025/05/16 20:56:25 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->start_mutex);
	while (philo->data->simulation_status == NOT_STARTED)
	{
		pthread_mutex_unlock(&philo->data->start_mutex);
		usleep(100);
		pthread_mutex_lock(&philo->data->start_mutex);
	}
	pthread_mutex_unlock(&philo->data->start_mutex);
}

int	end_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->start_mutex);
	if (philo->data->simulation_status == ENDED)
	{
		pthread_mutex_unlock(&philo->data->start_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->start_mutex);
	return (0);
}

static void	init_last_meal_time(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		philos[i].last_meal_time = data->time_start;
		action_log(&philos[i], "is thinking");
		i++;
	}
}

void	simulation_start(t_data *data, t_philo *philos)
{
	if (data->number_of_philosophers == 1)
		printf("The simulation has started with 1 philosopher...\n");
	else
		printf("The simulation has started with %d philosophers...\n",
			data->number_of_philosophers);
	pthread_mutex_lock(&data->start_mutex);
	gettimeofday(&data->time_start, NULL);
	init_last_meal_time(philos, data);
	data->simulation_status = STARTED;
	pthread_mutex_unlock(&data->start_mutex);
}
