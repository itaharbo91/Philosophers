/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:08:07 by itaharbo          #+#    #+#             */
/*   Updated: 2025/05/17 20:48:30 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	kill_processes(pid_t *pids, int num_of_philos)
{
	int	i;

	i = 0;
	while (i < num_of_philos)
	{
		kill(pids[i], SIGKILL);
		waitpid(pids[i], NULL, 0);
		i++;
	}
}

static void	simulation_start(t_data *data)
{
	if (data->number_of_philosophers == 1)
		printf("The simulation has started with 1 philosopher...\n");
	else
		printf("The simulation has started with %d philosophers...\n",
			data->number_of_philosophers);
}

int	main(int ac, char **av)
{
	t_data			data;
	t_semaphores	sema;
	pid_t			*pids;

	if (ac < 5 || ac > 6)
		return (write(2, "[Error]: invalid number of arguments!\n", 38), 1);
	if (parse_arg(ac, av, &data) != 0)
		return (1);
	if (init_semaphores(&sema, &data) != 0)
		return (1);
	data.semaphores = &sema;
	pids = malloc(sizeof(pid_t) * data.number_of_philosophers);
	if (!pids)
		return (write(2, "[Error]: malloc failed!\n", 24),
			free_semaphores(&sema), 1);
	simulation_start(&data);
	data.start_time = get_time();
	if (init_philos(&data, &sema, pids) != 0)
		return (free(pids), free_semaphores(&sema), 1);
	sem_wait(sema.simulation_end);
	kill_processes(pids, data.number_of_philosophers);
	printf("The simulation has ended.\n");
	free(pids);
	free_semaphores(&sema);
	return (0);
}
