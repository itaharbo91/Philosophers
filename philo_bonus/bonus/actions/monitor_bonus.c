/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:46:47 by itaharbo          #+#    #+#             */
/*   Updated: 2025/05/17 21:08:05 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_death(void *arg)
{
	t_philo		*philo;
	long long	time_diff;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->semaphores->sem_check);
		time_diff = get_time() - philo->last_meal_time;
		if (time_diff > philo->data->time_to_die)
		{
			action_log(philo, "died");
			sem_post(philo->semaphores->sem_check);
			return (NULL);
		}
		sem_post(philo->semaphores->sem_check);
		usleep(100);
	}
	return (NULL);
}
