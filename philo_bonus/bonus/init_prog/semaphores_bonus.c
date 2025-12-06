/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:38:30 by itaharbo          #+#    #+#             */
/*   Updated: 2025/05/17 20:51:53 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <fcntl.h>

static int	sem_bis(t_semaphores *sema)
{
	sema->simulation_end = sem_open("/simulation_end_sem",
			O_CREAT | O_EXCL, 0644, 0);
	if (sema->simulation_end == SEM_FAILED)
	{
		sem_close(sema->forks);
		sem_close(sema->print);
		sem_unlink("/forks_sem");
		sem_unlink("/print_sem");
		return (write(2, "[Error]: sem_open failed for simulation_end!\n",
				45), 1);
	}
	sema->meals = sem_open("/meals_sem", O_CREAT | O_EXCL, 0644, 1);
	if (sema->meals == SEM_FAILED)
	{
		sem_close(sema->forks);
		sem_close(sema->print);
		sem_close(sema->simulation_end);
		sem_unlink("/forks_sem");
		sem_unlink("/print_sem");
		sem_unlink("/simulation_end_sem");
		return (write(2, "[Error]: sem_open failed for meals!\n", 36), 1);
	}
	return (0);
}

static int	sem_open_check(t_semaphores *sema)
{
	sema->sem_check = sem_open("/sem_check", O_CREAT | O_EXCL, 0644, 1);
	if (sema->sem_check == SEM_FAILED)
	{
		sem_close(sema->forks);
		sem_close(sema->print);
		sem_close(sema->simulation_end);
		sem_close(sema->meals);
		sem_unlink("/forks_sem");
		sem_unlink("/print_sem");
		sem_unlink("/simulation_end_sem");
		sem_unlink("/meals_sem");
		return (write(2, "[Error]: sem_open failed for sem_check!\n", 40), 1);
	}
	return (0);
}

static int	sem_start(t_semaphores *sema)
{
	sema->start = sem_open("/start_sem", O_CREAT | O_EXCL, 0644, 0);
	if (sema->start == SEM_FAILED)
	{
		sem_close(sema->forks);
		sem_close(sema->print);
		sem_close(sema->simulation_end);
		sem_close(sema->meals);
		sem_close(sema->sem_check);
		sem_unlink("/forks_sem");
		sem_unlink("/print_sem");
		sem_unlink("/simulation_end_sem");
		sem_unlink("/meals_sem");
		sem_unlink("/sem_check");
		return (write(2, "[Error]: sem_open failed for start!\n", 36), 1);
	}
	return (0);
}

static int	sem_full(t_semaphores *sema)
{
	sema->sem_full = sem_open("/sem_full", O_CREAT | O_EXCL, 0644, 0);
	if (sema->sem_full == SEM_FAILED)
	{
		sem_close(sema->forks);
		sem_close(sema->print);
		sem_close(sema->simulation_end);
		sem_close(sema->meals);
		sem_close(sema->sem_check);
		sem_close(sema->start);
		sem_unlink("/forks_sem");
		sem_unlink("/print_sem");
		sem_unlink("/simulation_end_sem");
		sem_unlink("/meals_sem");
		sem_unlink("/sem_check");
		sem_unlink("/start_sem");
		return (write(2, "[Error]: sem_open failed for sem_full!\n", 40), 1);
	}
	return (0);
}

int	init_semaphores(t_semaphores *sema, t_data *data)
{
	unlink_semaphores();
	null_semaphores(sema);
	sema->forks = sem_open("/forks_sem", O_CREAT | O_EXCL, 0644,
			data->number_of_philosophers);
	if (sema->forks == SEM_FAILED)
		return (write(2, "[Error]: sem_open failed for forks!\n", 36), 1);
	sema->print = sem_open("/print_sem", O_CREAT | O_EXCL, 0644, 1);
	if (sema->print == SEM_FAILED)
	{
		sem_close(sema->forks);
		sem_unlink("/forks_sem");
		return (write(2, "[Error]: sem_open failed for print!\n", 36), 1);
	}
	if (sem_bis(sema) == 1)
		return (1);
	if (sem_open_check(sema) == 1)
		return (1);
	if (sem_start(sema) == 1)
		return (1);
	if (sem_full(sema) == 1)
		return (1);
	return (0);
}
