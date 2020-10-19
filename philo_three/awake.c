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

static int		create_threads_philos(t_philos *p)
{
	size_t		i;

	i = 0;
	while (i < p->size)
	{
		p->philo[i]->pid = fork();
		if (p->philo[i]->pid < 0)
			return (1);
		if (p->philo[i]->pid == 0)
		{
			if (pthread_create(&p->philo[i]->watcher, NULL,
					is_he_dead, p->philo[i]) != 0)
				exit(255);
			do_next(p->philo[i]);
			exit(0);
		}
		i++;
	}
	return (0);
}

static void		awake_mod_philos(t_philos *p, int n)
{
	size_t		i;

	i = 0;
	while (i < p->size)
	{
		if (i % 2 == n)
		{
			sem_post(p->philo[i]->started);
			usleep(1000 / p->size);
		}
		i++;
	}
}

int				awake_philos(t_philos *p)
{
	int		err;

	if (p->size == 0)
		return (0);
	err = create_threads_philos(p);
	if (err != 0)
		return (1);
	awake_mod_philos(p, 0);
	usleep(min(p->philo[0]->args.tt_die, p->philo[0]->args.tt_eat) * 500);
	awake_mod_philos(p, 1);
	return (0);
}

void			kill_philos(t_philos *p)
{
	size_t			i;

	i = 0;
	while (i < p->size)
	{
		if (p->philo[i] != 0)
		{
			sem_post(p->philo[i]->args.done);
			kill(p->philo[i]->pid, SIGTERM);
		}
		i++;
	}
}
