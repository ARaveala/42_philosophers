/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:48:18 by araveala          #+#    #+#             */
/*   Updated: 2024/07/25 16:08:56 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	time_stamp(size_t now, t_data *data)
{
	size_t	ret;

	ret = now - data->start_time;
	return (ret);
}

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	new_sleep(t_data *data, size_t wait)
{
	size_t	now;

	now = time_stamp(get_time(), data);
	while ((time_stamp(get_time(), data) - now) < wait)
	{
		if (check_flags(data, data->philo) == 0)
			return ;
		usleep(500);
	}
}
