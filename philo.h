/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut <alvanaut@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 00:20:27 by alvanaut          #+#    #+#             */
/*   Updated: 2025/07/02 15:15:13 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mtx;
typedef struct s_data	t_data;

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	bool				full;
	long				last_meal_time;
	t_fork				*left;
	t_fork				*right;
	pthread_t			thread_id;
	t_data				*data;
	pthread_mutex_t		last_meal_mutex;
}						t_philo;

typedef struct s_data
{
	long				nbr_philo;
	long				time_to_die;
	long				time_to_sleep;
	long				time_to_eat;
	long				limit_meals;
	long				start_simulation;
	bool				end_simulation;
	t_fork				*all_forks;
	t_philo				*all_philo;
	pthread_mutex_t		print_lock;
}						t_data;

void					init_fork(t_fork *fork, int id);
int						init_data(t_data *data, long nbr_philo);
int						init_mutexes(t_data *data);
void					init_philos(t_data *data);

void					destroy_forks(t_fork *forks, size_t count);
void					free_forks(t_data *data);
void					free_philos(t_data *data);
void					cleanup_data(t_data *data);

int						ft_atoi_positive(const char *str);
int						parse_args(int argc, char **argv, t_data *data);

void					*philo_routine(void *arg);
int						start_simulation(t_data *data);
void					ft_usleep(long duration);
void					philo_eat(t_philo *philo);
void					*death_checker(void *arg);
void					print_action(t_philo *philo, const char *msg);
void					destroy_all(t_data *data);
long					get_timestamp_ms(void);

#endif
