/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterrail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 11:14:22 by tterrail          #+#    #+#             */
/*   Updated: 2020/10/14 11:14:22 by tterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void 		announce_death(t_philo *this)
{
	sem_wait(this->args.end->tid);
	this->args.end->is_over = 1;
	print_unprotected(this, "died\n");
	sem_post(this->args.end->tid);
}

void		*is_he_dead(void *philo)
{
	t_philo	*this;
	int		over;

	this = (t_philo*)philo;
	while (1)
	{
		sem_wait(this->eating);
		sem_wait(this->args.end->tid);
		over = this->args.end->is_over;
		sem_post(this->args.end->tid);
		if (over == 1 || this->args.nb_of_must_eat == 0)
			break;
		if (is_dead(this) == 1)
		{
			if (over == 0)
			{
				announce_death(this);
				break ;
			}
		}
		sem_post(this->eating);
		usleep(1);
	}
	sem_post(this->eating);
	return (NULL);
}
