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

void		*is_he_dead(void *philo)
{
	t_philo	*this;

	this = (t_philo*)philo;
	pthread_mutex_lock(&this->eating);
	pthread_mutex_unlock(&this->eating);
	while (1)
	{
		pthread_mutex_lock(&this->eating);
		if (this->args.nb_of_must_eat == 0)
			break ;
		if (is_dead(this) == 1)
		{
			log_death(this->log, this);
			break ;
		}
		pthread_mutex_unlock(&this->eating);
		usleep(1000);
	}
	pthread_mutex_unlock(&this->eating);
	return (NULL);
}
