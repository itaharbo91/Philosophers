/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:38:30 by itaharbo          #+#    #+#             */
/*   Updated: 2025/05/07 14:36:06 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_creation(t_data *data, t_philo *philos)
{
	if (pthread_mutex_init(&data->start_mutex, NULL) != 0)
	{
		free_forks(data);
		free_philos(philos);
		free_data(data);
		return (write(2, "[Error]: pthread_mutex_init failed!\n", 36), 1);
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		free_forks(data);
		free_philos(philos);
		free_data(data);
		return (write(2, "[Error]: pthread_mutex_init failed!\n", 36), 1);
	}
	return (0);
}

int	philos_pthread_creation(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
		{
			free_pthread(philos, i);
			free_forks(data);
			free_philos(philos);
			free_data(data);
			return (1);
		}
		i++;
	}
	return (0);
}

int	thread_monitor(t_philo *philos, t_data *data, pthread_t *angel_of_death)
{
	if (pthread_create(angel_of_death, NULL, &monitoring, philos) != 0)
	{
		free_pthread(philos, data->number_of_philosophers);
		free_forks(data);
		free_philos(philos);
		free_data(data);
		return (1);
	}
	return (0);
}

static int	free_all(t_philo *philos, t_data *data)
{
	free_forks(data);
	free_philos(philos);
	free_data(data);
	return (0);
}

int	pthread_joining(t_philo *philos, t_data *data, pthread_t angel_of_death)
{
	int	i;
	int	join_failed;

	i = 0;
	join_failed = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
		{
			write(2, "[Error]: pthread_join failed for a thread!\n", 43);
			join_failed = 1;
		}
		i++;
	}
	if (pthread_join(angel_of_death, NULL) != 0)
	{
		write(2, "[Error]: pthread_join failed for the angel of death!\n", 54);
		join_failed = 1;
	}
	if (join_failed)
		return (free_all(philos, data), 1);
	free_all(philos, data);
	printf("The simulation has ended.\n");
	return (0);
}
