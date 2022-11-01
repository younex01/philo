/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelousse <yelousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 21:00:18 by yelousse          #+#    #+#             */
/*   Updated: 2022/08/28 15:05:03 by yelousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_loop(char *str, int *i, int *bool)
{
	long	resulte;

	resulte = 0;
	while (str[*i] != ' ' && str[*i])
	{
		*bool = 1;
		if (str[*i] >= '0' && str[*i] <= '9')
		{
			resulte = resulte * 10 + (str[*i] - '0');
			(*i)++;
		}
		else
			ft_error();
		if (resulte > 2147483647) //check this
			ft_error();
	}
	return (resulte);
}

int	ft_atoi(char *str)
{
	long	resulte;
	int		bool;
	int		i;

	bool = 0;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			ft_error();
		(i)++;
	}
	resulte = ft_atoi_loop(str, &(i), &bool);
	if (!bool)
		ft_error();
	return (resulte);
}
