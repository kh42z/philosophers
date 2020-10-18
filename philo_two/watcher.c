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
	while (1)
	{
		sem_wait(this->eating);
		if (this->args.nb_of_must_eat == 0)
			break ;
		if (is_dead(this) == 1)
		{
			log_death(this->log, this);
			break ;
		}
		sem_post(this->eating);
		usleep(1000);
	}
	sem_post(this->eating);
	return (NULL);
}
