/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 23:47:33 by itaharbo          #+#    #+#             */
/*   Updated: 2025/04/27 12:21:39 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_pthread(t_philo *philos, int number_of_philos)
{
	int	j;

	if (!philos)
		return ;
	j = 0;
	while (j < number_of_philos)
	{
		if (pthread_join(philos[j].thread, NULL) != 0)
			write(2, "[Error]: pthread_join failed for a thread!\n", 43);
		j++;
	}
}

void	*free_forks(t_data *data)
{
	int	i;

	if (!data->forks_mutex)
		return (NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks_mutex[i]);
		i++;
	}
	free(data->forks_mutex);
	data->forks_mutex = NULL;
	return (NULL);
}

void	*free_philos(t_philo *philos)
{
	int	i;

	if (!philos)
		return (NULL);
	i = 0;
	while (i < philos->data->number_of_philosophers)
	{
		pthread_mutex_destroy(&philos[i].philo_mutex);
		i++;
	}
	free(philos);
	philos = NULL;
	return (NULL);
}

void	*free_data(t_data *data)
{
	if (!data)
		return (NULL);
	pthread_mutex_destroy(&data->start_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	data->number_of_philosophers = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->number_of_times_each_philosopher_must_eat = 0;
	data->timestamp = 0;
	return (NULL);
}
