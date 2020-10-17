/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterrail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:45:56 by tterrail          #+#    #+#             */
/*   Updated: 2020/10/12 16:45:56 by tterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				is_dead(t_philo *this)
{
	long c;

	c = get_time_ms();
	if (c - this->ate_at > this->args.tt_die)
		return (1);
	return (0);
}

int				wait_ms(t_philo *this, suseconds_t timer)
{
	int				err;
	long			started_at;

	started_at = get_time_ms();
	while (get_time_ms() - started_at < timer)
	{
		err = usleep(1000);
		if (err != 0)
		{
			print_log(this, "USLEEP FAILED");
			return (1);
		}
	}
	return (0);
}

static void		think(t_philo *this)
{
	print_log(this, "is thinking\n");
	usleep(500);
}

void			do_stuff(t_philo *this)
{
	if (this->action == EATING)
	{
		sem_wait(this->forks);
		print_log(this, "has taken a fork\n");
		sem_wait(this->forks);
		print_log(this, "has taken a fork\n");
		print_log(this, "is eating\n");
		if (wait_ms(this, this->args.tt_eat) == 0)
		{
			sem_wait(this->eating);
			this->ate_at = get_time_ms();
			if (this->args.nb_of_must_eat > 0)
				this->args.nb_of_must_eat--;
			sem_post(this->eating);
		}
		sem_post(this->forks);
		sem_post(this->forks);
	}
	if (this->action == SLEEPING)
	{
		print_log(this, "is sleeping\n");
		wait_ms(this, this->args.tt_sleep);
	}
	if (this->action == THINKING)
		think(this);
}

void			*do_next(void *v)
{
	t_philo		*this;

	this = (t_philo*)v;
	sem_wait(this->started);
	sem_post(this->eating);
	while (is_dead(this) == 0 && this->args.nb_of_must_eat != 0)
	{
		this->action++;
		if (this->action > 2)
			this->action = 0;
		do_stuff(this);
	}
	pthread_join(this->watcher, NULL);
	sem_post(this->args.done);
	return (this);
}
