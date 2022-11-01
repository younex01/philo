/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 05:30:46 by yelousse          #+#    #+#             */
/*   Updated: 2022/08/28 05:48:00 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	nb_of_times_must_eat(t_philo *p)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < p->data->nb_of_philo)
	{
		if (p[i].nbr_eating >= p[i].data->nb_of_times_each_philo_must_eat
			&& p[i].data->ac == 6)
			count++;
	}
	if (count == p->data->nb_of_philo)
		return (0);
	return (1);
}

int	if_is_die(t_philo *p)
{
	int	i;

	i = -1;
	while (++i < p->data->nb_of_philo)
	{
		if (get_time() - p[i].last_eating_time > p[i].data->time_to_die)
		{
			sem_wait(p->data->print_sem);
			printf("%lld ms %d is died\n",
				get_time() - p->data->time, p[i].index + 1);
			return (0);
		}
	}
	return (1);
}

void	*routine(void *philo)
{
	t_philo	*p;

	p = philo;
	while (1)
	{
		if (!(nb_of_times_must_eat(p)))
			return (NULL);
		if (!(if_is_die(p)))
			return (NULL);
	}
}
