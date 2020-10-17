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
	int			err;

	i = 0;
	while (i < p->size)
	{
		err = pthread_create(&p->philo[i]->pid, NULL, do_next, p->philo[i]);
		if (err != 0)
			return (err);
		err = pthread_create(&p->philo[i]->watcher, NULL,
							 is_he_dead, p->philo[i]);
		if (err != 0)
			return (err);
		usleep(50);
		i++;
	}
	return (0);
}

static void 	awake_mod_philos(t_philos *p, int n, long started_at)
{
	size_t		i;

	i = 0;
	while (i < p->size)
	{
		if (i % 2 == n)
		{
			p->philo[i]->started_at = started_at;
			p->philo[i]->ate_at = started_at;
			sem_post(p->philo[i]->started);
			usleep(1000 / p->size);
		}
		i++;
	}
}

int				awake_philos(t_philos *p)
{
	int		err;
	long	started_at;

	if (p->size == 0)
		return (0);
	err = create_threads_philos(p);
	if (err != 0)
		return (1);
	started_at = get_time_ms();
	awake_mod_philos(p, 1, started_at);
	usleep(min(p->philo[0]->args.tt_die, p->philo[0]->args.tt_eat) * 500);
	awake_mod_philos(p, 0, started_at);
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
