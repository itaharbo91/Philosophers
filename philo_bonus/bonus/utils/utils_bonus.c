/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itaharbo <itaharbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:10:09 by itaharbo          #+#    #+#             */
/*   Updated: 2025/05/07 15:48:59 by itaharbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stddef.h>
#include <limits.h>

void	safe_sleep(long long time)
{
	long long	start;

	start = get_time();
	while (1)
	{
		if (get_time() - start >= time)
			break ;
		usleep(500);
	}
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	is_number(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

long long	valid_atoi(char *str)
{
	long long	num;
	size_t		i;

	num = 0;
	i = 0;
	while (str[i])
	{
		if ((!is_space(str[i]) && !is_number(str[i]))
			|| str[i] == '-' || str[i] == '+')
			return (-1);
		i++;
	}
	i = 0;
	while (is_space(str[i]))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		if (num > INT_MAX || num < 0)
			return (-1);
		i++;
	}
	while (is_space(str[i]))
		i++;
	return (num);
}
