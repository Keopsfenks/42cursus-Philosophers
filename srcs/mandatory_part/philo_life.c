/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 01:38:44 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/06 16:16:15 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	meal_control(t_philo *philo)
{
	if (philo->meal_count == philo->data->must_eat)
		return (false);
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
			pthread_mutex_lock(&philo->data->talk);
			philo->data->must_eat = -2;
		}
	}
}

bool	check(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead);
	if (get_tick_count() >= philo->data->t_to_die + philo->last_eat)
	{
		philo->data->dead_check = true;
		philo->dead_check = true;
		pthread_mutex_unlock(&philo->data->dead);
		pthread_mutex_lock(&philo->data->talk);
		return (false);
	}
	pthread_mutex_unlock(&philo->data->dead);
	return (true);
}

void	*philo_routine(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		time_machine(philo, philo->data->t_to_eat);
	while (check(philo) && meal_control(philo))
	{
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
	}
	check_finish(philo, philo->data);
	return (NULL);
}