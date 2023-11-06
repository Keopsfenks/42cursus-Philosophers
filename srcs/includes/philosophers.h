/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:43:12 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/06 03:21:53 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>


typedef struct s_philo
{
	int					id;
	int					eat_count;
	unsigned long		last_eat;
	bool				dead_check;
	int					meal_count;
	pthread_t			thread;
	pthread_mutex_t		*fork;
	struct s_data		*data;
	struct s_philo		*next;
	struct s_philo		*prev;
}						t_philo;

typedef struct s_data
{
	int				total_philos;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				must_eat;
	unsigned long	time;
	t_philo			*philo;
	bool			dead_check;
	pthread_mutex_t	dead;
	pthread_mutex_t	sleep;
	pthread_mutex_t	eat;
	pthread_mutex_t	talk;
}					t_data;

// LIST FUNCTIONS
t_philo			*philo_create(int type, t_data *data);
void			philo_add(t_philo **lst, t_philo *new);
t_philo			*ms_lstlast(t_philo *lst);
int				ms_lstsize(t_philo *lst);
// PHILO FUNCTIONS
int				ft_atoi(char *str);
void			ft_error(char *str);
unsigned long	get_tick_count(void);
void			take_forks(t_philo *philo);
void			*philo_routine(void *data);
void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_thinking(t_philo *philo);