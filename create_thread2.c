/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut < alvanaut@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:30:16 by alvanaut          #+#    #+#             */
/*   Updated: 2025/07/08 14:14:49 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_checker(void *arg)
{
	t_data	*data;
	size_t	i;

	data = (t_data *)arg;
	while (!is_simulation_ended(data))
	{
		i = 0;
		while (i < (size_t)data->nbr_philo && !is_simulation_ended(data))
		{
			if (check_philo_death(data, i))
				return (NULL);
			i++;
		}
		if (data->limit_meals > 0 && all_philos_ate_enough(data->all_philo,
				data->nbr_philo, data->limit_meals))
		{
			end_simulation(data);
			return (NULL);
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
	pthread_mutex_destroy(&data->end_simulation_lock);
	free(data->all_forks);
	free(data->all_philo);
}
