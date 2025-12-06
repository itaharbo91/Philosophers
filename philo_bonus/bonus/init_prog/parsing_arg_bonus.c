/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:01:50 by itaharbo          #+#    #+#             */
/*   Updated: 2025/05/07 15:56:58 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	parse_arg(int ac, char **av, t_data *data)
{
	data->number_of_philosophers = valid_atoi(av[1]);
	if (data->number_of_philosophers <= 0)
		return (write(2, "[Error]: invalid number of philosophers!\n", 41), 1);
	data->time_to_die = valid_atoi(av[2]);
	if (data->time_to_die <= 0)
		return (write(2, "[Error]: invalid time to die!\n", 30), 1);
	data->time_to_eat = valid_atoi(av[3]);
	if (data->time_to_eat <= 0)
		return (write(2, "[Error]: invalid time to eat!\n", 30), 1);
	data->time_to_sleep = valid_atoi(av[4]);
	if (data->time_to_sleep <= 0)
		return (write(2, "[Error]: invalid time to sleep!\n", 32), 1);
	if (ac == 6)
	{
		data->meals_required = valid_atoi(av[5]);
		if (data->meals_required < 0)
			return (write(2,
					"[Error]: invalid times each philo must eat!\n", 44), 1);
		if (data->meals_required == 0)
			return (write(1,
					"The simulation started and ended immediately!\n", 46), 1);
	}
	else if (ac == 5)
		data->meals_required = -1;
	return (0);
}
