/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:50:26 by araveala          #+#    #+#             */
/*   Updated: 2024/07/25 13:40:55 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_message(char *str, t_philosopher *t_philo, t_data *data)
{
	if (check_flags(data, t_philo) == 0)
		return (0);
	pthread_mutex_lock(&data->ultima);
	printf("%zu %d %s", time_stamp(get_time(), data), t_philo->philo_id, str);
	pthread_mutex_unlock(&data->ultima);
	return (1);
}

void	*one_philo(t_data *t_data, t_philosopher *t_philo)
{
	size_t	stamp;

	pthread_mutex_lock(t_philo->left_fork);
	pthread_mutex_lock(&t_data->ultima);
	stamp = time_stamp(get_time(), t_data);
	printf("%zu %d has taken a fork\n", stamp, t_philo->philo_id);
	pthread_mutex_unlock(&t_data->ultima);
	pthread_mutex_unlock(t_philo->left_fork);
	return (NULL);
}

int	ft_isdigit(int c)
{
	if (c >= 0060 && c <= 0071)
		return (1);
	return (0);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

long int	ft_atol(const char *str)
{
	int			save;
	long int	set_num;

	save = 1;
	set_num = 0;
	while (*str != '\0')
	{
		while ((*str > 8 && *str < 14) || *str == 32)
			str++;
		if (*str == '+' || *str == '-')
		{
			if (*str == '-')
				save = -1;
			str++;
		}
		while (ft_isdigit(*str) == 1)
		{
			set_num = set_num * 10 + *str - 48;
			str++;
		}
		return (set_num * save);
	}
	return (-1);
}
