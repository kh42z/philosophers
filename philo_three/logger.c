/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterrail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 10:23:07 by tterrail          #+#    #+#             */
/*   Updated: 2020/10/18 10:23:07 by tterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void					dump(t_log *this)
{
	write(STDOUT_FILENO, this->b1, this->cursor);
	this->cursor = 0;
}

static void				slowlog(t_log *this, t_philo *p,
							suseconds_t lock, suseconds_t write)
{
	add_number(this, get_time_ms() - p->started_at);
	add_number(this, p->id);
	add_str(this, "SLOW WRITE ");
	add_number(this, lock);
	add_number(this, write);
	this->b1[this->cursor++] = '\n';
	dump(this);
}

static void				print(t_log *this, t_philo *p, char *s)
{
	add_number(this, get_time_ms() - p->started_at);
	add_number(this, p->id);
	add_str(this, s);
	dump(this);
}

int						add(t_log *this, t_philo *p, char *s)
{
	long			start;
	long			lock_timer;
	long			write_timer;

	start = get_time_ms();
	sem_wait(this->tid);
	lock_timer = get_time_ms();
	print(this, p, s);
	if ((write_timer = get_time_ms()) - start > 3)
		slowlog(this, p,
			lock_timer - start, write_timer - start);
	sem_post(this->tid);
	return (0);
}

void					log_death(t_log *this, t_philo *p)
{
	sem_wait(this->tid);
	print(this, p, "died\n");
	dump(this);
}
