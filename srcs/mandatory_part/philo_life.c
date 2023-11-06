/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 01:38:44 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/07 01:36:20 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	meal_control(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat);
	if (philo->meal_count == philo->data->must_eat)
	{
		pthread_mutex_unlock(&philo->data->eat);
		return (false);
	}
	pthread_mutex_unlock(&philo->data->eat);
	return (true);
}

void	check_finish(t_philo *philo, t_data *data)
{
	int	i;
	int	x;

	if (philo->id == philo->data->total_philos)
	{
		i = -1;
		while (++i < philo->data->total_philos)
		{
			if (data->philo->meal_count == data->must_eat)
				x = 1;
			else
				x = 0;
			philo = philo->next;
		}
		if (philo->data->must_eat == philo->meal_count && x == 1)
		{
			pthread_mutex_lock(&philo->data->eat);
			philo->data->must_eat = -2;
			pthread_mutex_unlock(&philo->data->eat);
		}
	}
}

bool	check3(t_data *data)
{
	pthread_mutex_lock(&data->dead);
	if (data->dead_check == true)
	{
		pthread_mutex_unlock(&data->dead);
		return (false);
	}
	pthread_mutex_unlock(&data->dead);
	return (true);
}

void	*philo_routine(void *data)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		time_machine(philo, philo->data->t_to_eat);
	pthread_create(&thread, NULL, &dead_check, philo);
	pthread_detach(thread);
	while (check3(data) && meal_control(philo))
	{
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	check_finish(philo, philo->data);
	return (NULL);
}
