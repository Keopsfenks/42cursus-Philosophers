/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:02:09 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/07 01:42:23 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_args(t_data *data, int ac)
{
	if (data->total_philos <= 0)
		return (1);
	if (ac == 6)
		if (data->must_eat <= 0)
			return (1);
	if (data->t_to_eat < 60 || data->t_to_die < 60)
		return (1);
	if (data->t_to_sleep < 60)
		return (1);
	return (0);
}

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
	if (check_args(data, ac))
	{
		printf("Invalid arguments. \n");
		exit(1);
	}
	data->time = get_tick_count();
	data->dead_check = false;
	pthread_mutex_init(&data->dead, NULL);
	pthread_mutex_init(&data->eat, NULL);
	pthread_mutex_init(&data->talk, NULL);
	philo_initialize(data, &data->philo);
}

bool	which_dead_philo(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->dead);
		if (philo->data->dead_check == true)
		{
			if (philo->dead_check == true)
			{
				printf("%lld  %d died \n", \
					get_tick_count() - philo->data->time, philo->id);
				return (true);
			}
		}
		pthread_mutex_unlock(&philo->data->dead);
		if (philo->id == philo->data->total_philos)
			break ;
		philo = philo->next;
	}
	return (false);
}

void	free_data(t_data *data)
{
	long	i;

	i = -1;
	while (++i < data->total_philos)
	{
		pthread_mutex_destroy(data->philo->fork);
		usleep(50);
	}
	pthread_mutex_destroy(&(data->dead));
	pthread_mutex_destroy(&(data->eat));
	pthread_mutex_destroy(&(data->talk));
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
			if (which_dead_philo(data->philo))
				break ;
			pthread_mutex_lock(&data->eat);
			if (data->must_eat == -2)
			{
				printf("There's no food left in the pot. \n");
				pthread_mutex_unlock(&data->eat);
				break ;
			}
			pthread_mutex_unlock(&data->eat);
			usleep(500);
		}
	}
	else
		ft_error("You gave incomplete or too many arguments!");
	free_data(data);
}
