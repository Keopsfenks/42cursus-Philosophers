/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 04:13:21 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/06 15:45:07 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->prev->fork);
	pthread_mutex_lock(&philo->data->talk);
	printf ("%lld  %d has taken a fork \n", \
		get_tick_count() - philo->data->time, philo->id);
	pthread_mutex_unlock(&philo->data->talk);
	pthread_mutex_lock(philo->fork);
	pthread_mutex_lock(&philo->data->talk);
	printf ("%lld  %d has taken a fork \n", \
		get_tick_count() - philo->data->time, philo->id);
	pthread_mutex_unlock(&philo->data->talk);
}

void	philo_eating(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->data->talk);
	printf("%lld  %d is eating \n",
		get_tick_count() - philo->data->time, philo->id);
	pthread_mutex_unlock(&philo->data->talk);
	pthread_mutex_lock(&philo->data->eat);
	philo->meal_count++;
	philo->last_eat = get_tick_count();
	pthread_mutex_unlock(&philo->data->eat);
	time_machine(philo, philo->data->t_to_eat);
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->prev->fork);
}

void	philo_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->talk);
	printf("%lld  %d is sleeping\n",
		get_tick_count() - philo->data->time, philo->id);
	pthread_mutex_unlock(&philo->data->talk);
	pthread_mutex_lock(&philo->data->sleep);
	time_machine(philo, philo->data->t_to_sleep);
	pthread_mutex_unlock(&philo->data->sleep);
}

void	philo_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->talk);
	printf("%lld  %d is thinking\n",
		get_tick_count() - philo->data->time, philo->id);
	pthread_mutex_unlock(&philo->data->talk);
}