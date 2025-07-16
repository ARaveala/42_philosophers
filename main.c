/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:37:42 by araveala          #+#    #+#             */
/*   Updated: 2024/07/31 12:22:22 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_flags(t_data *data, t_philosopher *t_philo)
{
	pthread_mutex_lock(&data->death_lock);
	if (data->death_flag == 1)
	{
		pthread_mutex_unlock(&data->death_lock);
		return (0);
	}
	else
		pthread_mutex_unlock(&data->death_lock);
	pthread_mutex_lock(&t_philo->meal_lock);
	if (data->meal_flag == 1)
	{
		pthread_mutex_unlock(&t_philo->meal_lock);
		return (0);
	}
	else
		pthread_mutex_unlock(&t_philo->meal_lock);
	return (1);
}

void	check_dead(t_data *data, t_philosopher *philo)
{
	size_t	now;

	pthread_mutex_lock(&philo->meal_lock);
	now = time_stamp(get_time(), data) - philo->last_meal;
	if (now >= data->time_to_die)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		pthread_mutex_lock(&data->death_lock);
		data->death_flag = 1;
		pthread_mutex_unlock(&data->death_lock);
		pthread_mutex_lock(&data->ultima);
		printf("%zu %d died\n", time_stamp(get_time(), data), philo->philo_id);
		pthread_mutex_unlock(&data->ultima);
	}
	else
		pthread_mutex_unlock(&philo->meal_lock);
}

void	check_full(t_data *data, t_philosopher *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (philo->meals > data->num_of_meals)
	{
		data->meal_flag++;
		pthread_mutex_unlock(&philo->meal_lock);
	}
	else
		pthread_mutex_unlock(&philo->meal_lock);
}

void	check_check(t_data *data, t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		check_dead(data, &philo[i]);
		if (data->num_of_meals > 0)
			check_full(data, &philo[i]);
		if (check_flags(data, philo) == 0)
			break ;
		i++;
	}
}

int	main(int argc, char **argv)
{
	static t_data	*data;

	if (check_input(argc, argv) == 1)
		return (1);
	data = malloc(sizeof(t_data) * 1);
	if (data == NULL)
		return (1);
	if (init_data(data, argv) == 1)
	{
		free(data);
		return (1);
	}
	if (init_philo(data) == 1)
	{
		free(data);
		return (1);
	}
	create_threads(data);
	join_threads(data);
	destroy_things(data, 5, data->num_of_philos, data->num_of_philos);
	return (0);
}
