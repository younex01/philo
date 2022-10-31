/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 05:44:06 by yelousse          #+#    #+#             */
/*   Updated: 2022/08/28 15:03:54 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(void)
{
	write(2, "Error\n", 6);
	return ; // check this
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

void	ft_usleep(unsigned long time)
{
	unsigned long	timenow;

	timenow = get_time();
	while (get_time() - timenow < time)
		usleep(50);
}

void	ft_print(const char *s, long long time, int i, pthread_mutex_t m)
{
	pthread_mutex_lock(&m);
	printf("%lld ms %d %s\n", time, i, s);
	pthread_mutex_unlock(&m);
}

void	ft_destroy_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&philo->data->print_mutex);
	while (i < philo->data->nb_of_philo)
	{
		pthread_mutex_destroy(&philo[i].fork);
		i++;
	}
}

int	taking_forks(t_philo *p)
{
	if (p->index % 2 == 0)
	{
		pthread_mutex_lock(&p->fork);
		ft_print("has taken a fork", get_time() - p->time,
			p->index + 1, p->data->print_mutex);
		if (! p->next_fork)
			return (0);
		pthread_mutex_lock(p->next_fork);
		ft_print("has taken a fork", get_time() - p->time,
			p->index + 1, p->data->print_mutex);
	}
	else
	{
		pthread_mutex_lock(p->next_fork);
		ft_print("has taken a fork", get_time() - p->time,
			p->index + 1, p->data->print_mutex);
		pthread_mutex_lock(&p->fork);
		ft_print("has taken a fork", get_time() - p->time,
			p->index + 1, p->data->print_mutex);
	}
	return (1);
}
