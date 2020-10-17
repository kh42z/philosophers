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
	this->end->is_over = 1;
	print_unprotected(this, "died\n");
}

void		*is_he_dead(void *philo)
{
	t_philo	*this;

	this = (t_philo*)philo;
	pthread_mutex_lock(&this->eating);
	pthread_mutex_unlock(&this->eating);
	while (1)
	{
		pthread_mutex_lock(&this->end->tid);
		pthread_mutex_lock(&this->eating);
		if (this->end->is_over == 1 || this->args.nb_of_must_eat == 0)
			break ;
		if (is_dead(this) == 1)
		{
			if (this->end->is_over == 0)
			{
				announce_death(this);
				break ;
			}
		}
		pthread_mutex_unlock(&this->eating);
		pthread_mutex_unlock(&this->end->tid);
		usleep(1000);
	}
	pthread_mutex_unlock(&this->end->tid);
	pthread_mutex_unlock(&this->eating);
	return (NULL);
}
