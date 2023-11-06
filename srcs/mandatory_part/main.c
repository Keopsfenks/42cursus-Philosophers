/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:02:09 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/06 16:13:15 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	data_initialize(t_data *data, int ac, char **av)
{
	data->total_philos = ft_atoi(av[1]);
	data->t_to_die = ft_atoi(av[2]);
	data->t_to_eat = ft_atoi(av[3]);
	data->t_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = -1;
	data->time = get_tick_count();
	data->dead_check = false;
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->sleep, NULL);
	pthread_mutex_init(&data->eat, NULL);
	pthread_mutex_init(&data->talk, NULL);
	philo_initialize(data, &data->philo);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (ac > 4 && ac < 7)
	{
		data_initialize(data, ac, av);
		while (1)
		{
			if (dead_check(data->philo))
				break ;
			if (data->must_eat == -2)
			{
				printf("There's no food left in the pot. \n");
				break ;
			}
			usleep(500);
		}
	}
	else
		ft_error("You gave incomplete or too many arguments!");
}
