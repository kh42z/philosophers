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
	if (get_time_ms() - this->ate_at >= this->args.tt_die)
		return (1);
	return (0);
}

int				wait_ms(t_philo *this, suseconds_t timer)
{
	int				err;
	long			started_at;
	long			latest;

	started_at = get_time_us();
	while ((latest = get_time_us()) - started_at < timer * 1000)
	{
		if ((started_at + timer * 1000) - latest > 1000)
			err = usleep((started_at + (timer * 1000) - latest) / 2);
		else
			err = usleep((started_at + (timer * 1000)) - latest);
		if (err != 0)
		{
			add(this->log, this, "USLEEP FAILED\n");
			return (1);
		}
	}
	if (latest - (started_at + timer * 1000) > 2000)
		add(this->log, this, "OVERLOAD\n");
	return (0);
}

static void		ate(t_philo *this)
{
	pthread_mutex_lock(&this->eating);
	this->ate_at = get_time_ms();
	if (this->args.nb_of_must_eat > 0)
		this->args.nb_of_must_eat--;
	pthread_mutex_unlock(&this->eating);
}

int				do_stuff(t_philo *this)
{
	int is_over;

	is_over = 0;
	if (this->action == EATING)
	{
		pthread_mutex_lock(&this->left->tid);
		if (add(this->log, this, "has taken a fork\n") == 1)
			is_over = 1;
		pthread_mutex_lock(&this->right->tid);
		add(this->log, this, "has taken a fork\n");
		add(this->log, this, "is eating\n");
		if (wait_ms(this, this->args.tt_eat) == 0)
			ate(this);
		pthread_mutex_unlock(&this->right->tid);
		pthread_mutex_unlock(&this->left->tid);
	}
	if (this->action == SLEEPING)
	{
		add(this->log, this, "is sleeping\n");
		wait_ms(this, this->args.tt_sleep);
	}
	if (this->action == THINKING)
		add(this->log, this, "is thinking\n");
	return (is_over);
}

void			*do_next(void *v)
{
	t_philo		*this;

	this = (t_philo*)v;
	pthread_mutex_lock(&this->started);
	pthread_mutex_unlock(&this->eating);
	while (is_dead(this) == 0 && this->args.nb_of_must_eat != 0)
	{
		this->action++;
		if (this->action > 2)
			this->action = 0;
		if (do_stuff(this) == 1)
			break ;
	}
	pthread_join(this->watcher, NULL);
	return (this);
}
