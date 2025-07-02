/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut <alvanaut@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:06:53 by alvanaut          #+#    #+#             */
/*   Updated: 2025/07/02 15:05:51 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_positive(const char *str)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	if (!str || !str[0])
		return (-1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		res = res * 10 + (str[i] - '0');
		if (res > INT_MAX)
			return (-1);
		i++;
	}
	if (res == 0)
		return (-1);
	return ((int)res);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
    return (fprintf(stderr,
        "Usage: %s nbr_philo time_to_die time_to_eat time_to_sleep "
        "[limit_meals]\n",
        argv[0]), 1);
	data->nbr_philo = ft_atoi_positive(argv[1]);
	data->time_to_die = ft_atoi_positive(argv[2]) * 1000;
	data->time_to_eat = ft_atoi_positive(argv[3]) * 1000;
	data->time_to_sleep = ft_atoi_positive(argv[4]) * 1000;
	data->limit_meals = -1;
	if (argc == 6)
		data->limit_meals = ft_atoi_positive(argv[5]);
	if (data->nbr_philo <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
		return (fprintf(stderr,
				"Arguments must be strictly positive integers\n"), 1);
	if (argc == 6 && data->limit_meals <= 0)
		return (fprintf(stderr,
				"limit_meals must be a strictly positive integer\n"), 1);
	return (0);
}
