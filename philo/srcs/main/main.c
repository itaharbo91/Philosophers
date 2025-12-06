/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:09:50 by itaharbo          #+#    #+#             */
/*   Updated: 2025/05/07 16:10:24 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_data(t_data *data)
{
	data->number_of_philosophers = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->number_of_times_each_philosopher_must_eat = 0;
	data->philos_full = 0;
	data->timestamp = 0;
	data->forks_mutex = 0;
	data->simulation_status = NOT_STARTED;
}

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		*philos;
	pthread_t	angel_of_death;

	if (ac < 5 || ac > 6)
		return (write(2, "[Error]: invalid number of arguments!\n", 38), 1);
	philos = NULL;
	angel_of_death = 0;
	init_data(&data);
	if (parse_arg(ac, av, &data) != 0)
		return (1);
	if (philos_creation(&data, &philos) != 0)
		return (1);
	if (mutex_creation(&data, philos) != 0)
		return (1);
	if (philos_pthread_creation(philos, &data) != 0)
		return (1);
	if (thread_monitor(philos, &data, &angel_of_death) != 0)
		return (1);
	simulation_start(&data, philos);
	if (pthread_joining(philos, &data, angel_of_death) != 0)
		return (1);
	return (0);
}
