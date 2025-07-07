/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvanaut < alvanaut@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:04:19 by alvanaut          #+#    #+#             */
/*   Updated: 2025/07/05 11:32:01 by alvanaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_args(argc, argv, &data))
		return (1);
	if (init_data(&data, data.nbr_philo))
	{
		printf("Error: failed to initialize data\n");
		return (1);
	}
	if (start_simulation(&data))
	{
		printf("Error: failed to start simulation\n");
		cleanup_data(&data);
		return (1);
	}
	cleanup_data(&data);
	return (0);
}
