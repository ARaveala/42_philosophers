/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:04:46 by araveala          #+#    #+#             */
/*   Updated: 2024/07/31 15:43:39 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forks(t_data *data, t_philosopher *t_philo)
{
	pthread_mutex_lock(t_philo->left_fork);
	print_message("has taken a fork\n", t_philo, data);
	pthread_mutex_lock(t_philo->right_fork);
	print_message("has taken a fork\n", t_philo, data);
	return (1);
}

int	eating(t_data *data, t_philosopher *t_philo)
{
	forks(data, t_philo);
	if (print_message("is eating\n", t_philo, data) == 0)
	{
		pthread_mutex_unlock(t_philo->right_fork);
		pthread_mutex_unlock(t_philo->left_fork);
		return (0);
	}
	pthread_mutex_lock(&t_philo->meal_lock);
	t_philo->last_meal = time_stamp(get_time(), data);
	pthread_mutex_unlock(&t_philo->meal_lock);
	new_sleep(data, data->time_to_eat);
	pthread_mutex_lock(&t_philo->meal_lock);
	t_philo->meals++;
	pthread_mutex_unlock(&t_philo->meal_lock);
	pthread_mutex_unlock(t_philo->right_fork);
	pthread_mutex_unlock(t_philo->left_fork);
	return (1);
}

void	*act(void *data)
{
	t_data			*t_data;
	t_philosopher	*t_philo;

	t_philo = (t_philosopher *)data;
	t_data = t_philo->data;
	if (t_data->num_of_philos == 1)
		return (one_philo(t_data, t_philo));
	if (t_data->num_of_philos > 1 && t_philo->philo_id % 2 != 0)
	{
		print_message("is thinking\n", t_philo, t_data);
		new_sleep(t_data, t_data->time_to_die / 10);
	}
	while (check_flags(t_data, t_philo) == 1)
	{
		if (eating(t_data, t_philo) == 0)
			break ;
		if (print_message("is sleeping\n", t_philo, t_data) == 0)
			break ;
		new_sleep(t_data, t_data->time_to_sleep);
		if (print_message("is thinking\n", t_philo, t_data) == 0)
			break ;
	}
	return (NULL);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	if (data->fail_num > 0)
	{
		while (i < data->fail_num)
		{
			pthread_join(data->philo[i].thrd_id, NULL);
			i++;
		}
		return (1);
	}
	else
	{
		while (i < data->num_of_philos)
		{
			pthread_join(data->philo[i].thrd_id, NULL);
			i++;
		}
	}
	return (0);
}

int	create_threads(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->num_of_philos)
	{
		if (pthread_create(&d->philo[i].thrd_id, NULL, &act, &d->philo[i]) != 0)
		{
			d->fail_num = i;
			printf("thread creation issue\n");
			break ;
		}
		i++;
	}
	while (d->death_flag == 0 && d->meal_flag == 0)
	{
		check_check(d, d->philo);
		if (check_flags(d, d->philo) == 0)
			break ;
	}
	return (1);
}
