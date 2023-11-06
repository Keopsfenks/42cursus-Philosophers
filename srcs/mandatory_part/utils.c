/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:09:32 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/06 15:50:45 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_error(char *str)
{
	printf("%s", str);
	exit(1);
}

int	ft_atoi(char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			ft_error("The argument you enter cannot be a negative number");
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		result = result * 10 + (str[i] - 48) * sign;
		// if (result > 200)
		// 	ft_error("You gave argument overcome limit!");
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
		ft_error("More than one same sign in given argument!");
	return ((int)result);
}

long long	get_tick_count(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	time_machine(t_philo *philo, long long pass_time)
{
	long long	time;

	time = get_tick_count();
	(void)philo;
	while (get_tick_count() - time < pass_time)
		usleep(100);
}

bool	dead_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead);
	while (1)
	{
		if (philo->dead_check == true)
		{
			printf("%lld  %d died \n", \
				get_tick_count() - philo->data->time, philo->id);
			return (true);
		}
		if (philo->id == philo->data->total_philos)
			break ;
		philo = philo->next;
	}
	pthread_mutex_unlock(&philo->data->dead);
	return (false);
}