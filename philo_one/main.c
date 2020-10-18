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

void			init_log(t_args *args, t_log *log)
{
	log->cursor = 0;
	log->sim_over = 0;
	pthread_mutex_init(&log->tid, NULL);
	args->log = log;
}

int				error_msg(char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	write(STDERR_FILENO, s, i);
	return (1);
}

int				main(int argc, char *argv[])
{
	t_args				args;
	t_philos			philos;
	t_forks				forks;
	t_log				log;

	if (argc < 5 || argc > 6 || parse_args(&args, argc, argv) == 1)
		return (error_msg("Usage: ./philo_one 2 200 100 100"));
	init_log(&args, &log);
	if (new_forks(&forks, args.nb_of_philos) != 0)
		return (error_msg("Unable to create forks"));
	if (spawn_philos(&args, &philos, &forks) != 0)
	{
		delete_forks(&forks);
		return (error_msg("Unable to spawn philos"));
	}
	awake_philos(&philos);
	wait_philos(&philos, &args);
	empty_buffer(&log);
	pthread_mutex_destroy(&log.tid);
	delete_forks(&forks);
	delete_philos(&philos);
	return (0);
}
