/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_log.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:35:18 by itaharbo          #+#    #+#             */
/*   Updated: 2025/05/07 15:48:11 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	action_log(t_philo *philos, char *action)
{
	long long		timestamp_in_ms;

	timestamp_in_ms = get_time() - (philos->data->time_start.tv_sec * 1000
			+ philos->data->time_start.tv_usec / 1000);
	pthread_mutex_lock(&philos->data->print_mutex);
	printf("%lld %d %s\n", timestamp_in_ms, philos->number, action);
	pthread_mutex_unlock(&philos->data->print_mutex);
}
