/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut < alvanaut@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:59:50 by alvanaut          #+#    #+#             */
/*   Updated: 2025/07/07 14:25:37 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, const char *msg)
{
	if (is_simulation_ended(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->print_lock);
	if (!is_simulation_ended(philo->data))
		printf("%ld %d %s\n", get_timestamp_ms()
			- philo->data->start_simulation, philo->id + 1, msg);
	pthread_mutex_unlock(&philo->data->print_lock);
}
