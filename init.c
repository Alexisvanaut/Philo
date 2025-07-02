/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut <alvanaut@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:10:46 by alvanaut          #+#    #+#             */
/*   Updated: 2025/07/02 15:14:54 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// initialiser la structure data
// initialiser la structure fork
// initialiser la structure philo

int	init_mutexes(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < (size_t)data->nbr_philo)
	{
		if (pthread_mutex_init(&data->all_forks[i].fork, NULL) != 0)
		{
			destroy_forks(data->all_forks, i);
			return (1);
		}
		data->all_forks[i].fork_id = i;
		i++;
	}
	return (0);
}

int	init_data(t_data *data, long nbr_philo)
{
	data->nbr_philo = nbr_philo;
	data->end_simulation = false;
	data->start_simulation = 0;
	data->time_to_die = 0;
	data->time_to_sleep = 0;
	data->limit_meals = 0;
	data->all_forks = malloc(sizeof(t_fork) * nbr_philo);
	data->all_philo = malloc(sizeof(t_philo) * nbr_philo);
	if (!data->all_forks || !data->all_philo)
	{
		cleanup_data(data);
		return (1);
	}
	if (init_mutexes(data))
	{
		cleanup_data(data);
		return (1);
	}
	init_philos(data);
	return (0);
}

void	init_fork(t_fork *fork, int id)
{
	if (pthread_mutex_init(&fork->fork, NULL) != 0)
		fork->fork_id = id;
}

void init_philos(t_data *data)
{
	size_t	i;
	t_philo	*philo;

	i = 0;
	while (i < (size_t)data->nbr_philo)
	{
		philo = &data->all_philo[i];
		philo->id = i;
		philo->meals_counter = 0;
		philo->full = false;
		philo->last_meal_time = 0;
		philo->data = data;
		philo->left = &data->all_forks[i];
		philo->right = &data->all_forks[(i + 1) % data->nbr_philo];
		pthread_mutex_init(&philo->last_meal_mutex, NULL);  // <-- init
		i++;
	}
}
