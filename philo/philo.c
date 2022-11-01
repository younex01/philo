/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 21:00:22 by yelousse          #+#    #+#             */
/*   Updated: 2022/08/28 15:06:35 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_init(t_philo *philo, t_data_g *data_g)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data_g->print_mutex, NULL);
	data_g->print_check = 0;
	data_g->time = get_time();
	while (i < data_g->nb_of_philo)
	{
		pthread_mutex_init(&philo[i].fork, NULL);
		philo[i].nbr_eating = 0;
		philo[i].next_fork = NULL;
		philo[i].index = i;
		philo[i].data = data_g;
		philo[i].last_eating_time = get_time();
		i++;
	}
}

void	*philo_routine(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (p->index % 2)
		usleep(50);
	while (1)
	{
		if (!taking_forks(p))
			break ;
		p->last_eating_time = get_time();
		ft_print("is eating", get_time() - p->data->time,
			p->index + 1, p);
		p->nbr_eating++;
		ft_usleep(p->data->time_to_eat);
		pthread_mutex_unlock(&p->fork);
		pthread_mutex_unlock(p->next_fork);
		ft_print("is sleeping", get_time() - p->data->time, p->index + 1, p);
		ft_usleep(p->data->time_to_sleep);
		ft_print("is thinking", get_time() - p->data->time, p->index + 1, p);
	}
	return (NULL);
}

void	create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_of_philo)
	{
		pthread_create(&philo[i].th, NULL, &philo_routine, &philo[i]);
		pthread_detach(philo[i].th);
		i++;
	}
}

void	create_philo(t_data_g	*data_g)
{
	t_philo		*philo;
	pthread_t	monitor;

	philo = malloc(data_g->nb_of_philo * sizeof(t_philo));
	if (!philo)
		return ;
	philo_init(philo, data_g);
	link_forks(philo);
	create_threads(philo);
	pthread_create(&monitor, NULL, &routine, philo);
	pthread_join(monitor, NULL);
	//free(philo);
	ft_destroy_mutex(philo);
}

int	main(int ac, char **av)
{
	t_data_g	data_g;

	data_g.par_check = 0;
	if (ac == 5 || ac == 6)
	{
		data_g.nb_of_philo = ft_atoi(av[1]);
		data_g.time_to_die = ft_atoi(av[2]);
		data_g.time_to_eat = ft_atoi(av[3]);
		data_g.time_to_sleep = ft_atoi(av[4]);
		check_par(&data_g);
		if (data_g.par_check == 1)
			return (0);
		if (ac == 6)
		{
			data_g.nb_of_times_each_philo_must_eat = ft_atoi(av[5]);
			if (data_g.nb_of_times_each_philo_must_eat <= 0)
				return (0);
			data_g.ac = 6;
		}
		create_philo(&data_g);
	}
	else
		ft_error();
	return (0);
}
