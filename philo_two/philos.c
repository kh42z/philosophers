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

int				is_dead(t_philo *this)
{
	if (get_time_ms() - this->ate_at > this->args.tt_die)
		return (1);
	return (0);
}

sem_t			*create_sem(t_philo *this, char prefix)
{
	static char		name[255];
	int				i;
	unsigned int	id;

	i = 2;
	name[0] = prefix;
	name[1] = '_';
	id = this->id;
	while (id > 0)
	{
		name[i] = (id % 10) + '0';
		id /= 10;
		++i;
	}
	name[i] = '\0';
	sem_unlink(name);
	return (sem_open(name, O_CREAT, 0660, 0));
}

t_philo			*new_philo(t_args *args, unsigned int i)
{
	t_philo *p;

	p = malloc(sizeof(t_philo));
	if (p == NULL)
		return (NULL);
	memset(p, 0, sizeof(t_philo));
	p->log = args->log;
	p->args = *args;
	p->id = i + 1;
	p->action = THINKING;
	p->forks = args->forks;
	p->eating = create_sem(p, 'e');
	p->started = create_sem(p, 's');
	if (p->eating == SEM_FAILED || p->started == SEM_FAILED)
	{
		free(p);
		return (NULL);
	}
	return (p);
}

int				spawn_philos(t_args *args, t_philos *philos)
{
	int		i;

	philos->size = 0;
	philos->philo = malloc(sizeof(t_philo*) * args->nb_of_philos);
	if (!philos->philo)
		return (-1);
	while (philos->size < args->nb_of_philos)
	{
		i = philos->size;
		philos->philo[i] = new_philo(args, i);
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
		sem_close(philos->philo[philos->size - 1]->started);
		free(philos->philo[philos->size - 1]);
		--philos->size;
	}
	free(philos->philo);
}
