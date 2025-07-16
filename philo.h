/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araveala <araveala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:26:18 by araveala          #+#    #+#             */
/*   Updated: 2024/07/31 12:20:56 by araveala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

// the philosopher
typedef pthread_mutex_t			t_mx;
typedef struct s_philosopher	t_philosopher;

typedef struct s_data
{
	t_mx			*main_fork_lock;
	t_mx			ultima;
	t_mx			death_lock;
	size_t			start_time;
	size_t			time_to_die;
	int				death_flag;
	int				meal_flag;	
	int				num_of_philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	int				fail_num;
	t_philosopher	*philo;
}	t_data;

typedef struct s_philosopher
{
	size_t			last_meal;
	int				meals;
	pthread_t		thrd_id;
	int				philo_id;
	t_mx			meal_lock;
	t_mx			*right_fork;
	t_mx			*left_fork;
	t_data			*data;
}	t_philosopher;

// user_input checks
int			argument_count(int argc);
int			string_valid(char **argv);
int			check_input(int argc, char **argv);

// utils
long int	ft_atol(const char *str);
void		*one_philo(t_data *t_data, t_philosopher *t_philo);
int			ft_isdigit(int c); //is char digit
int			ft_strlen(char *s);
int			print_message(char *str, t_philosopher *t_philo, t_data *data);
// time utils
size_t		get_time(void);
size_t		time_stamp(size_t now, t_data *data);//t_philosopher *philo);
void		new_sleep(t_data *data, size_t wait);
// init data 
int			quick_check(long int num);//(t_data *data);
int			init_data(t_data *data, char **argv);
int			init_philo(t_data *data);
int			set_data_mutex(t_data *data);
//main
int			main(int argc, char **argv);
int			check_flags(t_data *data, t_philosopher *t_philo);
void		check_dead(t_data *data, t_philosopher *philo);
void		check_full(t_data *data, t_philosopher *philo);
void		check_check(t_data *data, t_philosopher *philo);

// philo
int			eating(t_data *data, t_philosopher *t_philo);
int			forks(t_data *data, t_philosopher *t_philo);
int			join_threads(t_data *data);
int			create_threads(t_data *d);
void		*act(void *data);

// free things
int			destroy_things(t_data *data, int step, int i, int x);
#endif
