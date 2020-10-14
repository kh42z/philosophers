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
	if (get_time_ms() - this->ate_at > this->args.tt_die)
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

void			do_stuff(t_philo *this)
{
	if (this->action == EATING)
	{
		pthread_mutex_lock(&this->left->tid);
		print_log(this, "has taken a fork\n");
		pthread_mutex_lock(&this->right->tid);
		print_log(this, "has taken a fork\n");
		print_log(this, "is eating\n");
		if (wait_ms(this, this->args.tt_eat) == 0)
		{
			pthread_mutex_lock(&this->eating);
			this->ate_at = get_time_ms();
			pthread_mutex_unlock(&this->eating);
			if (this->args.nb_of_must_eat > 0)
				this->args.nb_of_must_eat--;
		}
		pthread_mutex_unlock(&this->right->tid);
		pthread_mutex_unlock(&this->left->tid);
	}
	if (this->action == SLEEPING)
	{
		print_log(this, "is sleeping\n");
		wait_ms(this, this->args.tt_sleep);
	}
	if (this->action == THINKING)
		print_log(this, "is thinking\n");
}

void			*do_next(void *v)
{
	t_philo		*this;
	int			over;

	this = (t_philo*)v;
	while (is_dead(this) == 0 && this->args.nb_of_must_eat != 0)
	{
		pthread_mutex_lock(&this->end->tid);
		over = this->end->is_over;
		pthread_mutex_unlock(&this->end->tid);
		if (over == 1)
			break ;
		this->action++;
		if (this->action > 2)
			this->action = 0;
		do_stuff(this);
	}
	pthread_join(this->watcher, NULL);
	return (this);
}
