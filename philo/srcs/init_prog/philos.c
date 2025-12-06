/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:00:41 by itaharbo          #+#    #+#             */
/*   Updated: 2025/04/29 15:47:14 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	forks_creation(t_data *data)
{
	int	i;
	int	j;

	data->forks_mutex = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	if (!data->forks_mutex)
		return (write(2, "[Error]: malloc failed!\n", 24), 1);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->forks_mutex[i], NULL) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&data->forks_mutex[j]);
				j++;
			}
			free(data->forks_mutex);
			return (write(2, "[Error]: pthread_mutex_init failed!\n", 36), 1);
		}
		i++;
	}
	return (0);
}

static int	init_philos(t_philo *philos, t_data *data, int i)
{
	philos[i].number = i + 1;
	philos[i].times_eaten = 0;
	philos[i].last_meal_time.tv_sec = 0;
	philos[i].thread = 0;
	philos[i].data = data;
	philos[i].left_fork = &data->forks_mutex[i];
	philos[i].right_fork = &data->forks_mutex[(i + 1)
		% data->number_of_philosophers];
	if (pthread_mutex_init(&philos[i].philo_mutex, NULL) != 0)
	{
		free(data->forks_mutex);
		return (write(2, "[Error]: pthread_mutex_init failed!\n", 36), 1);
	}
	return (0);
}

int	philos_creation(t_data *data, t_philo **philos)
{
	int	i;

	if (forks_creation(data))
		return (1);
	*philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!*philos)
	{
		free_forks(data);
		return (write(2, "[Error]: malloc failed!\n", 24), 1);
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (init_philos(*philos, data, i) != 0)
		{
			free_forks(data);
			free_philos(*philos);
			free_data(data);
			return (1);
		}
		i++;
	}
	return (0);
}
