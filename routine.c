/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut <alvanaut@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:49:04 by alvanaut          #+#    #+#             */
/*   Updated: 2025/07/02 15:40:36 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_timestamp_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

int	take_forks(t_philo *philo)
{
	if (philo->data->nbr_philo == 1)
	{
		pthread_mutex_lock(&philo->left->fork);
		print_action(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die + 1);
		pthread_mutex_unlock(&philo->left->fork);
		return (1);
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left->fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right->fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->right->fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left->fork);
		print_action(philo, "has taken a fork");
	}
	return (0);
}

void	philo_eat(t_philo *philo)
{
	if (take_forks(philo))
		return ;
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal_time = get_timestamp_ms();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	philo->meals_counter++;
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->left->fork);
	pthread_mutex_unlock(&philo->right->fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(900);
	while (!philo->data->end_simulation)
	{
		philo_eat(philo);
		if (philo->data->limit_meals > 0
			&& philo->meals_counter >= philo->data->limit_meals)
			break ;
		print_action(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		print_action(philo, "is thinking");
	}
	return (NULL);
}

void	*death_checker(void *arg)
{
	t_data *data;
	size_t i;
	long time_since_last_meal;

	data = (t_data *)arg;
	while (!data->end_simulation)
	{
		i = 0;
		while (i < (size_t)data->nbr_philo)
		{
			pthread_mutex_lock(&data->all_philo[i].last_meal_mutex);
			time_since_last_meal = get_timestamp_ms()
				- data->all_philo[i].last_meal_time;
			pthread_mutex_unlock(&data->all_philo[i].last_meal_mutex);
			if (time_since_last_meal > data->time_to_die)
			{
				data->end_simulation = true;
				pthread_mutex_lock(&data->print_lock);
				printf("%ld %d died\n", get_timestamp_ms()
					- data->start_simulation, data->all_philo[i].id + 1);
				pthread_mutex_unlock(&data->print_lock);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
