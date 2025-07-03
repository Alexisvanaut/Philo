/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut <alvanaut@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:47:22 by alvanaut          #+#    #+#             */
/*   Updated: 2025/07/02 15:49:36 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long duration_ms)
{
	long	start;
	long	elapsed;

	start = get_timestamp_ms();
	while (1)
	{
		elapsed = get_timestamp_ms() - start;
		if (elapsed >= duration_ms)
			break;
		usleep(100); // Réduire pour plus de précision
	}
}

static void	init_philo_timestamps(t_data *data)
{
	size_t i;

	i = 0;
	while (i < (size_t)data->nbr_philo)
	{
		data->all_philo[i].last_meal_time = data->start_simulation;
		i++;
	}
}

static int	create_all_threads(t_data *data, pthread_t *monitor)
{
	size_t i;

	if (pthread_create(monitor, NULL, &death_checker, data) != 0)
		return (1);
	i = 0;
	while (i < (size_t)data->nbr_philo)
	{
		if (pthread_create(&data->all_philo[i].thread_id, NULL, &philo_routine,
				&data->all_philo[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

static void	join_all_threads(t_data *data, pthread_t monitor)
{
	size_t i;

	i = 0;
	while (i < (size_t)data->nbr_philo)
		pthread_join(data->all_philo[i++].thread_id, NULL);
	pthread_join(monitor, NULL);
}

int	start_simulation(t_data *data)
{
	pthread_t monitor;

	data->start_simulation = get_timestamp_ms();
	init_philo_timestamps(data);
	if (create_all_threads(data, &monitor))
		return (1);
	join_all_threads(data, monitor);
	return (0);
}

void	destroy_all(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < (size_t)data->nbr_philo)
	{
		pthread_mutex_destroy(&data->all_forks[i].fork);
		pthread_mutex_destroy(&data->all_philo[i].last_meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	free(data->all_forks);
	free(data->all_philo);
}