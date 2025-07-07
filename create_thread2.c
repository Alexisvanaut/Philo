/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut < alvanaut@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:30:16 by alvanaut          #+#    #+#             */
/*   Updated: 2025/07/05 11:31:05 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_checker(void *arg)
{
	t_data	*data;
	size_t	i;

	data = (t_data *)arg;
	while (!data->end_simulation)
	{
		i = 0;
		while (i < (size_t)data->nbr_philo && !data->end_simulation)
		{
			if (check_philo_death(data, i))
				return (NULL);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

int	all_philos_ate_enough(t_philo *philos, int nb_philos, int must_eat)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < nb_philos)
	{
		if (philos[i].meals_counter >= must_eat)
			count++;
		i++;
	}
	return (count == nb_philos);
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
