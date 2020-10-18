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

int			init_sem(t_args *args, t_log *log)
{
	log->cursor = 0;
	log->sim_over = 0;
	args->log = log;
	sem_unlink(SEM_LOG);
	sem_unlink(SEM_FORKS);
	args->forks = sem_open(SEM_FORKS, O_CREAT, 0660, args->nb_of_philos);
	args->log->tid = sem_open(SEM_LOG, O_CREAT, 0660, 1);
	if (args->forks == SEM_FAILED || args->log->tid == SEM_FAILED)
		return (1);
	return (0);
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
	t_log				log;

	if (argc < 5 || argc > 6 || parse_args(&args, argc, argv) == 1)
		return (error_msg("Usage: ./philo_one 2 200 100 100"));
	if (init_sem(&args, &log))
		return (error_msg("unable to create sem_t"));
	if (spawn_philos(&args, &philos) != 0)
		return (error_msg("Unable to spawn philos"));
	awake_philos(&philos);
	wait_philos(&philos, &args);
	empty_buffer(&log);
	sem_close(args.log->tid);
	sem_close(args.forks);
	delete_philos(&philos);
	return (0);
}
