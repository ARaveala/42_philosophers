/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:37:03 by araveala          #+#    #+#             */
/*   Updated: 2024/07/31 13:03:51 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	quick_validity_check(t_data *data, int x)
{
	if (data->num_of_philos < 1)
		return (-1);
	if (data->time_to_die <= 0)
		return (-1);
	if (data->time_to_eat == -1)
		return (-1);
	if (data->time_to_sleep == -1)
		return (-1);
	if (x == 0)
	{
		if (data->num_of_meals == -1 || data->num_of_meals == 0)
			return (-1);
	}
	else if (x == 1)
		data->num_of_meals = -10;
	return (1);
}

int	quick_check(long int num)
{
	if (num <= 0)
	{
		printf("number cant be 0 or less\n");
		return (-1);
	}
	if (num < -2147483648 || num > 2147483)
	{
		printf("system overload: number will crash pc\n");
		return (-1);
	}
	else
		return ((int)num);
}

int	set_data_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->main_fork_lock = malloc(sizeof(t_mx) * data->num_of_philos);
	if (data->main_fork_lock == NULL)
		return (1);
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->main_fork_lock[i], NULL) != 0)
			return (destroy_things(data, 1, i, 0));
		i++;
	}
	if (pthread_mutex_init(&data->ultima, NULL) != 0)
		return (destroy_things(data, 1, i, 0));
	if (pthread_mutex_init(&data->death_lock, NULL) != 0)
		return (destroy_things(data, 2, i, 0));
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	int	x;

	x = 1;
	data->num_of_philos = quick_check(ft_atol(argv[1]));
	data->time_to_die = quick_check(ft_atol(argv[2]));
	data->time_to_eat = quick_check(ft_atol(argv[3]));
	data->time_to_sleep = quick_check(ft_atol(argv[4]));
	data->start_time = get_time();
	data->death_flag = 0;
	data->meal_flag = 0;
	data->fail_num = 0;
	if (argv[5] != NULL)
	{
		data->num_of_meals = quick_check(ft_atol(argv[5]));
		x = 0;
	}
	if (quick_validity_check(data, x) == -1)
		return (1);
	if (set_data_mutex(data) == 1)
		return (1);
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;
	int	calc;

	i = -1;
	data->philo = malloc (data->num_of_philos * (sizeof(t_philosopher)));
	if (data->philo == NULL)
		return (destroy_things(data, 3, data->num_of_philos, 0));
	while (++i < data->num_of_philos)
	{
		calc = (i + 1) % data->num_of_philos;
		data->philo[i].philo_id = i + 1;
		data->philo[i].meals = 0;
		data->philo[i].data = data;
		data->philo[i].right_fork = &data->main_fork_lock[i];
		data->philo[i].left_fork = &data->main_fork_lock[calc];
		data->philo[i].last_meal = 0;
		if (pthread_mutex_init(&data->philo[i].meal_lock, NULL) != 0)
		{
			destroy_things(data, 4, data->num_of_philos, i);
			free(data->philo);
			return (1);
		}		
	}
	return (0);
}
