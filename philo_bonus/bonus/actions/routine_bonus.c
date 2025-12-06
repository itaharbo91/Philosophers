/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:45:40 by itaharbo          #+#    #+#             */
/*   Updated: 2025/05/17 21:50:11 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	inside_routine(t_philo *philo, int *meals)
{
	sem_wait(philo->semaphores->forks);
	action_log(philo, "has taken a fork");
	sem_wait(philo->semaphores->forks);
	action_log(philo, "has taken a fork");
	action_log(philo, "is eating");
	sem_wait(philo->semaphores->sem_check);
	philo->last_meal_time = get_time();
	sem_post(philo->semaphores->sem_check);
	safe_sleep(philo->data->time_to_eat);
	if (philo->data->meals_required != -1)
	{
		(*meals)++;
		if ((*meals) == philo->data->meals_required)
			sem_post(philo->semaphores->sem_full);
	}
	sem_post(philo->semaphores->forks);
	sem_post(philo->semaphores->forks);
	action_log(philo, "is sleeping");
	safe_sleep(philo->data->time_to_sleep);
	action_log(philo, "is thinking");
	return (0);
}

int	philo_routine(t_philo *philo)
{
	pthread_t	monitor;
	int			diff;
	int			meals;

	action_log(philo, "is thinking");
	if (pthread_create(&monitor, NULL, monitor_death, philo) != 0)
	{
		write(2, "[Error]: pthread_create failed!\n", 33);
		return (1);
	}
	pthread_detach(monitor);
	sem_wait(philo->semaphores->start);
	if (philo->number % 2 == 0)
		usleep(2000);
	meals = 0;
	while (1)
	{
		inside_routine(philo, &meals);
		diff = (philo->data->time_to_eat - philo->data->time_to_sleep);
		if (diff > 0)
			usleep(diff * 2000);
		else
			usleep(2000);
	}
	return (0);
}
