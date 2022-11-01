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
	exit(1) ; // check this
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

void	ft_print(const char *s, long long time, int i, t_philo *ph)
{
	(void)time;

	sem_wait(ph->data->print_sem);
    //  if (ph->data->print_check)
    //      return ;
 	printf("%lld ms %d %s\n", get_time() - ph->data->time, i, s);
	sem_post(ph->data->print_sem);
}

void	ft_destroy_sem(t_philo *philo)
{
	int	i;

	i = 0;
	sem_close(philo->data->print_sem);
	while (i < philo->data->nb_of_philo)
	{
		sem_close(philo[i].fork);
		i++;
	}
	free(philo);
}

int	taking_forks(t_philo *p)
{
	if (p->index % 2 == 0)
	{
		sem_wait(p->fork);
		ft_print("has taken a fork", get_time() - p->data->time, p->index + 1, p);
		sem_wait(p->fork);
		ft_print("has taken a fork", get_time() - p->data->time, p->index + 1, p);
	}
	return (1);
}
