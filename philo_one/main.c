/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterrail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:45:48 by tterrail          #+#    #+#             */
/*   Updated: 2020/10/12 16:45:48 by tterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			init_mutex(t_args *args, t_end *end, pthread_mutex_t *log_mutex)
{
	memset(end, 0, sizeof(t_end));
	pthread_mutex_init(log_mutex, NULL);
	pthread_mutex_init(&end->tid, NULL);
	args->print = log_mutex;
	args->end = end;
}

int				main(int argc, char *argv[])
{
	t_args				args;
	t_philos			philos;
	t_forks				forks;
	t_end				end;
	pthread_mutex_t		log_mutex;

	if (argc < 5 || argc > 6 || parse_args(&args, argc, argv) == 1)
	{
		write(STDERR_FILENO, "Invalid arguments\n", 19);
		return (1);
	}
	init_mutex(&args, &end, &log_mutex);
	if (new_forks(&forks, args.nb_of_philos) != 0)
		return (1);
	if (spawn_philos(&args, &philos, &forks) != 0)
	{
		delete_forks(&forks);
		return (1);
	}
	if (awake_philos(&philos) == 0)
		wait_philos(&philos);
	delete_forks(&forks);
	delete_philos(&philos);
	return (0);
}
