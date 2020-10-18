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

static void				dump(t_log *this)
{
	if (this->cursor < BUFFER_SIZE / 2 && this->sim_over == 0)
		return ;
	write(STDOUT_FILENO, this->b1, this->cursor);
	this->cursor = 0;
}

void					empty_buffer(t_log *this)
{
	sem_wait(this->tid);
	dump(this);
	sem_post(this->tid);
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

	start = get_time_ms();
	sem_wait(this->tid);
	if (this->sim_over == 1)
	{
		sem_post(this->tid);
		return (1);
	}
	print(this, p, s);
	if (get_time_ms() - start > 3)
		print(this, p, "SLOW PRINT");
	sem_post(this->tid);
	return (0);
}

void					log_death(t_log *this, t_philo *p)
{
	sem_wait(this->tid);
	if (this->sim_over == 1)
	{
		sem_post(this->tid);
		return ;
	}
	print(this, p, "died\n");
	this->sim_over = 1;
	dump(this);
	sem_post(this->tid);
}
