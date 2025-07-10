/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut < alvanaut@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:31:00 by alvanaut          #+#    #+#             */
/*   Updated: 2025/07/07 14:25:56 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks(t_fork *forks, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&forks[i].fork);
		i++;
	}
}

void	free_forks(t_data *data)
{
	if (data->all_forks)
	{
		destroy_forks(data->all_forks, data->nbr_philo);
		free(data->all_forks);
		data->all_forks = NULL;
	}
}

void	free_philos(t_data *data)
{
	size_t	i;

	if (data->all_philo)
	{
		i = 0;
		while (i < (size_t)data->nbr_philo)
		{
			pthread_mutex_destroy(&data->all_philo[i].last_meal_mutex);
			i++;
		}
		free(data->all_philo);
		data->all_philo = NULL;
	}
}

void	cleanup_data(t_data *data)
{
	free_forks(data);
	free_philos(data);
	pthread_mutex_destroy(&data->end_simulation_lock);
	pthread_mutex_destroy(&data->print_lock);
}
