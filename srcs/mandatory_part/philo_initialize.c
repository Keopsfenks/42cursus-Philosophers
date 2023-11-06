/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 23:23:25 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/06 15:25:05 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_philo	*philo_create(int type, t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->fork = malloc(sizeof(pthread_mutex_t));
	if (!philo)
		return (NULL);
	philo->id = type + 1;
	philo->last_eat = get_tick_count();
	philo->meal_count = 0;
	philo->data = data;
	philo->dead_check = false;
	pthread_mutex_init(philo->fork, NULL);
	philo->next = NULL;
	philo->prev = NULL;
	return (philo);
}

void	philo_add(t_philo **lst, t_philo *new)
{
	t_philo	*tmp;

	tmp = ms_lstlast(*lst);
	if (!tmp)
		*lst = new;
	else
	{
		tmp->next = new;
		new->prev = tmp;
	}
}

t_philo	*ms_lstlast(t_philo *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		else
			lst = lst->next;
	}
	return (lst);
}

void	start(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->total_philos)
	{
		pthread_create(&philo->thread, NULL, &philo_routine, philo);
		pthread_detach(philo->thread);
		philo = philo->next;	
	}
}

void	philo_initialize(t_data *data, t_philo **philo)
{
	int		i;
	t_philo	*last;

	i = -1;
	while (++i < data->total_philos)
		philo_add(&(*philo), philo_create(i, data));
	last = ms_lstlast(*philo);
	last->next = (*philo);
	(*philo)->prev = last;
	start(*philo);
}