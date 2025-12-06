/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_log_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:35:18 by itaharbo          #+#    #+#             */
/*   Updated: 2025/05/15 23:24:02 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	action_log(t_philo *philos, char *action)
{
	long long		timestamp_in_ms;

	sem_wait(philos->semaphores->print);
	timestamp_in_ms = get_time() - philos->data->start_time;
	printf("%lld %d %s\n", timestamp_in_ms, philos->number, action);
	if (action[0] == 'd')
		sem_post(philos->semaphores->simulation_end);
	else
		sem_post(philos->semaphores->print);
}
