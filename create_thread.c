/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut <alvanaut@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:47:22 by alvanaut          #+#    #+#             */
/*   Updated: 2025/07/02 15:20:35 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long duration)
{
	long	start;

	start = get_timestamp_ms();
	while ((get_timestamp_ms() - start) < duration)
		usleep(100);
}

int	start_simulation(t_data *data)
{
	size_t		i;
	pthread_t	monitor;

	data->start_simulation = get_timestamp_ms();

	if (pthread_create(&monitor, NULL, &death_checker, data) != 0)
		return (1);

	i = 0;
	while (i < (size_t)data->nbr_philo)
	{
		data->all_philo[i].last_meal_time = data->start_simulation;
		if (pthread_create(&data->all_philo[i].thread_id, NULL, &philo_routine,
				&data->all_philo[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < (size_t)data->nbr_philo)
		pthread_join(data->all_philo[i++].thread_id, NULL);

	pthread_join(monitor, NULL);
	return (0);
}

void	destroy_all(t_data *data)
{
	size_t i;

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