/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 21:00:22 by yelousse          #+#    #+#             */
/*   Updated: 2023/01/17 00:51:54 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_routine(t_philo *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (1)
	{
		if (!taking_forks(p))
			break ;
		p->last_eating_time = get_time();
		ft_print("is eating", get_time() - p->data->time,
				 p->index + 1, p);
		p->nbr_eating++;
		ft_usleep(p->data->time_to_eat);
		sem_post(p->fork);
		sem_post(p->fork);
		ft_print("is sleeping", get_time() - p->data->time, p->index + 1, p);
		ft_usleep(p->data->time_to_sleep);
		ft_print("is thinking", get_time() - p->data->time, p->index + 1, p);
	}
}

void	philo_init(t_philo *philo, t_data_g *data_g)
{
	int	i;
	int id;
	pthread_t	monitor;

	i = 0;
	sem_unlink("forks");
	sem_unlink("print");
	data_g->print_sem = sem_open("print", O_CREAT, 0777, 1);
	philo->fork = sem_open("forks", O_CREAT, 0777, data_g->nb_of_philo);
	data_g->time = get_time();
	while (i < data_g->nb_of_philo)
	{
		id = fork();
		if(id == 0)
		{
			philo[i].nbr_eating = 0;
			philo[i].index = i;
			philo[i].data = data_g;
			philo[i].last_eating_time = get_time();
			// create_threads(philo, i);
			pthread_create(&monitor, NULL, &routine, philo);
			philo_routine(philo);
			break;
		}
		else
			philo[i].id = id;
		i++;
	}
}


// void	create_threads(t_philo *philo, int i)
// {
	
// 	// pthread_detach(philo[i].th);
// }

void	create_philo(t_data_g	*data_g)
{
	t_philo		*philo;

	philo = malloc(data_g->nb_of_philo * sizeof(t_philo));
	if (!philo)
		return ;
	// philo->id = malloc(data_g->nb_of_philo * sizeof(int));
	// if (!philo->id)
	// 	return ;
	philo_init(philo, data_g);
	ft_destroy_sem(philo);
}

int	main(int ac, char **av)
{
	t_data_g	data_g;

	if (ac == 5 || ac == 6)
	{
		data_g.nb_of_philo = ft_atoi(av[1]);
		if (!data_g.nb_of_philo)
			ft_error();
		data_g.time_to_die = ft_atoi(av[2]);
		data_g.time_to_eat = ft_atoi(av[3]);
		data_g.time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
		{
			data_g.nb_of_times_each_philo_must_eat = ft_atoi(av[5]);
			data_g.ac = 6;
		}
		create_philo(&data_g);
	}
	return (0);
}
