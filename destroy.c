/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut < alvanaut@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:31:00 by alvanaut          #+#    #+#             */
/*   Updated: 2025/07/05 11:21:00 by alvanaut         ###   ########.fr       */
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
	if (data->all_philo)
	{
		free(data->all_philo);
		data->all_philo = NULL;
	}
}

void	cleanup_data(t_data *data)
{
	free_forks(data);
	free_philos(data);
}
