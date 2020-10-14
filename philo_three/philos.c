/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterrail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 17:00:33 by tterrail          #+#    #+#             */
/*   Updated: 2020/10/12 17:00:33 by tterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			create_eating_mutex(t_philo *this) {
	static char		name[255];
	int				i;
	unsigned int	id;

	i = 2;
	name[0] = 'p';
	name[1] = '_';
	id = this->id;
	while (id > 0) {
		name[i] = (id % 10) + '0';
		id /= 10;
		++i;
	}
	name[i] = '\0';
	sem_unlink(name);
	this->eating = sem_open(name, O_CREAT, 0660, 1);
}


t_philo			*new_philo(t_args *args, long started_at,
				unsigned int i)
{
	t_philo *p;

	p = malloc(sizeof(t_philo));
	if (p == NULL)
		return (NULL);
	memset(p, 0, sizeof(t_philo));
	p->forks = args->forks;
	p->args = *args;
	p->id = i + 1;
	p->action = THINKING;
	p->ate_at = started_at;
	p->started_at = started_at;
	create_eating_mutex(p);
	if (p->eating == SEM_FAILED)
	{
		free(p);
		return (NULL);
	}
	return (p);
}

int				spawn_philos(t_args *args, t_philos *philos)
{
	int		i;
	long	started_at;

	philos->size = 0;
	started_at = get_time_ms();
	philos->philo = malloc(sizeof(t_philo*) * args->nb_of_philos);
	if (!philos->philo)
		return (-1);
	while (philos->size < args->nb_of_philos)
	{
		i = philos->size;
		philos->philo[i] = new_philo(args, started_at, i);
		if (philos->philo[i] == NULL)
		{
			delete_philos(philos);
			return (-1);
		}
		philos->size++;
	}
	return (0);
}

void			delete_philos(t_philos *philos)
{
	while (philos->size > 0)
	{
		sem_close(philos->philo[philos->size - 1]->eating);
		free(philos->philo[philos->size - 1]);
		--philos->size;
	}
	free(philos->philo);
}
