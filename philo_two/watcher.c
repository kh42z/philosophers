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

static void	announce_death(t_philo *this)
{
	this->args.end->is_over = 1;
	print_unprotected(this, "died\n");
}

void		*is_he_dead(void *philo)
{
	t_philo	*this;

	this = (t_philo*)philo;
	while (1)
	{
		sem_wait(this->eating);
		sem_wait(this->args.end->tid);
		if (is_dead(this) == 1)
		{
			if (this->args.end->is_over == 1 || this->args.nb_of_must_eat == 0)
				break ;
			if (this->args.end->is_over == 0)
			{
				announce_death(this);
				break ;
			}
		}
		sem_post(this->args.end->tid);
		sem_post(this->eating);
		usleep(1);
	}
	sem_post(this->args.end->tid);
	sem_post(this->eating);
	return (NULL);
}
