/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:56:36 by araveala          #+#    #+#             */
/*   Updated: 2024/07/31 13:04:51 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_things(t_data *data, int step, int i, int x)
{
	if (step > 0)
	{
		while (--i >= 0)
			pthread_mutex_destroy(&data->main_fork_lock[i]);
		if (step > 1)
			pthread_mutex_destroy(&data->ultima);
		if (step > 2)
			pthread_mutex_destroy(&data->death_lock);
		free(data->main_fork_lock);
		if (step > 3)
		{
			while (--x >= 0)
				pthread_mutex_destroy(&data->philo[x].meal_lock);
		}
		if (step > 4)
		{
			free(data->philo);
			free(data);
		}
	}
	return (1);
}
