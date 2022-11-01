/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 05:31:00 by yelousse          #+#    #+#             */
/*   Updated: 2022/08/28 15:04:11 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data_g
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_times_each_philo_must_eat;
	pthread_mutex_t	print_mutex;
	int				ac;
	int				print_check;
	long long		time;
	int				par_check;
}t_data_g;

typedef struct s_philo
{
	pthread_t		th;
	pthread_mutex_t	fork;
	pthread_mutex_t	*next_fork;
	long long		last_eating_time;
	int				nbr_eating;
	int				index;
	int				timestamp_in_ms;
	t_data_g		*data;
}t_philo;

void		link_forks(t_philo *philo);
int			ft_atoi(char *str);
void		*routine(void *philo);
long long	get_time(void);
void		ft_usleep(unsigned long time);
void		ft_print(const char *s, long long time, int i, t_philo *ph);
void		ft_destroy_mutex(t_philo *philo);
int			taking_forks(t_philo *p);
void		ft_error(void);
void		check_par(t_data_g *data);

#endif