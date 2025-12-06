/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:43:14 by itaharbo          #+#    #+#             */
/*   Updated: 2025/04/28 22:04:50 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks_even(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (end_status(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	action_log(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	if (end_status(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	action_log(philo, "has taken a fork");
	return (0);
}

static int	take_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (end_status(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	action_log(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	if (end_status(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	action_log(philo, "has taken a fork");
	return (0);
}

static void	eating_mutex_unlock(t_philo *philo)
{
	if (philo->number % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

static void	eating_action(t_philo *philo)
{
	action_log(philo, "is eating");
	pthread_mutex_lock(&philo->philo_mutex);
	gettimeofday(&philo->last_meal_time, NULL);
	pthread_mutex_unlock(&philo->philo_mutex);
}

void	is_eating(t_philo *philo)
{
	if (end_status(philo))
		return ;
	if (philo->number % 2 == 0)
		if (take_forks_even(philo))
			return ;
	if (philo->number % 2 != 0)
		if (take_forks_odd(philo))
			return ;
	eating_action(philo);
	if (end_status(philo))
	{
		eating_mutex_unlock(philo);
		return ;
	}
	safe_sleep(philo->data->time_to_eat, philo);
	if (end_status(philo))
	{
		eating_mutex_unlock(philo);
		return ;
	}
	pthread_mutex_lock(&philo->philo_mutex);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->philo_mutex);
	eating_mutex_unlock(philo);
}
