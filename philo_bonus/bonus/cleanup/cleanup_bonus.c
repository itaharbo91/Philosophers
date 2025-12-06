/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:25:24 by itaharbo          #+#    #+#             */
/*   Updated: 2025/05/17 19:39:29 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	null_semaphores(t_semaphores *sema)
{
	sema->forks = NULL;
	sema->print = NULL;
	sema->simulation_end = NULL;
	sema->meals = NULL;
	sema->sem_check = NULL;
	sema->start = NULL;
	sema->sem_full = NULL;
}

void	unlink_semaphores(void)
{
	sem_unlink("/forks_sem");
	sem_unlink("/print_sem");
	sem_unlink("/simulation_end_sem");
	sem_unlink("/meals_sem");
	sem_unlink("/sem_check");
	sem_unlink("/start_sem");
	sem_unlink("/sem_full");
}

void	free_semaphores(t_semaphores *sema)
{
	if (sema->forks && sema->forks != SEM_FAILED)
		sem_close(sema->forks);
	if (sema->print && sema->print != SEM_FAILED)
		sem_close(sema->print);
	if (sema->simulation_end && sema->simulation_end != SEM_FAILED)
		sem_close(sema->simulation_end);
	if (sema->meals && sema->meals != SEM_FAILED)
		sem_close(sema->meals);
	if (sema->sem_check && sema->sem_check != SEM_FAILED)
		sem_close(sema->sem_check);
	if (sema->start && sema->start != SEM_FAILED)
		sem_close(sema->start);
	if (sema->sem_full && sema->sem_full != SEM_FAILED)
		sem_close(sema->sem_full);
	unlink_semaphores();
}
