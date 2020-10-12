/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterrail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 17:00:33 by tterrail          #+#    #+#             */
/*   Updated: 2020/10/12 17:00:33 by tterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo			*new_philo(t_args *args, t_forks *forks, long started_at,
				unsigned int i)
{
	t_philo *p;

	p = malloc(sizeof(t_philo));
	if (p == NULL)
		return (NULL);
	memset(p, 0, sizeof(t_philo));
	p->print = args->print;
	p->end = args->end;
	p->args = *args;
	p->id = i + 1;
	p->action = THINKING;
	p->ate_at = started_at;
	p->started_at = started_at;
	p->left = forks->items[i];
	if (i + 1 == args->nb_of_philos)
		p->right = forks->items[0];
	else
		p->right = forks->items[i + 1];
	return (p);
}

int				spawn_philos(t_args *args, t_philos *philos, t_forks *forks)
{
	int		i;
	long	started_at;

	philos->size = 0;
	started_at = get_time_ms();
	philos->philo = malloc(sizeof(t_philo*) * args->nb_of_philos);
	if (!philos->philo)
		return (-1);
	while (philos->size < args->nb_of_philos)
	{
		i = philos->size;
		philos->philo[i] = new_philo(args, forks, started_at, i);
		if (philos->philo[i] == NULL)
		{
			delete_philos(philos);
			return (-1);
		}
		philos->size++;
	}
	return (0);
}

void			delete_philos(t_philos *philos)
{
	while (philos->size > 0)
	{
		free(philos->philo[philos->size - 1]);
		--philos->size;
	}
	free(philos->philo);
}
