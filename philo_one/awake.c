/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   awake.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterrail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:46:32 by tterrail          #+#    #+#             */
/*   Updated: 2020/10/12 16:46:32 by tterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int		awake_mod_philos(t_philos *p, short n)
{
	size_t		i;
	int			err;

	i = 0;
	while (i < p->size)
	{
		if (i % 2 == n)
		{
			err = pthread_create(&p->philo[i]->pid, NULL, do_next, p->philo[i]);
			if (err != 0)
				return (err);
			err = pthread_create(&p->philo[i]->watcher, NULL,
					is_he_dead, p->philo[i]);
			if (err != 0)
				return (err);
		}
		i++;
	}
	return (0);
}

static int		awake_even_philos(t_philos *p)
{
	return (awake_mod_philos(p, 0));
}

static int		awake_odd_philos(t_philos *p)
{
	return (awake_mod_philos(p, 1));
}

int				awake_philos(t_philos *p)
{
	int err;

	if ((err = awake_even_philos(p)) != 0)
		return (err);
	usleep(p->philo[0]->args.tt_eat * 500);
	if ((err = awake_odd_philos(p)) != 0)
		return (err);
	return (0);
}

void			wait_philos(t_philos *p)
{
	size_t			i;

	i = 0;
	while (i < p->size)
	{
		pthread_join(p->philo[i]->pid, NULL);
		i++;
	}
}
