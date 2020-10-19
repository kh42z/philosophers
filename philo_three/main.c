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

int				init_sem(t_args *args, t_log *log)
{
	log->cursor = 0;
	args->log = log;
	sem_unlink(SEM_LOG);
	sem_unlink(SEM_END);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_DONE);
	args->forks = sem_open(SEM_FORKS, O_CREAT, 0660, args->nb_of_philos);
	args->log->tid = sem_open(SEM_LOG, O_CREAT, 0660, 1);
	args->end = sem_open(SEM_END, O_CREAT, 0660, 0);
	args->done = sem_open(SEM_DONE, O_CREAT, 0660, 0);
	if (args->forks == SEM_FAILED || args->log->tid == SEM_FAILED ||
		args->end == SEM_FAILED || args->done == SEM_FAILED)
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

void			close_sem(t_args *args)
{
	sem_close(args->end);
	sem_close(args->log->tid);
	sem_close(args->done);
	sem_close(args->forks);
}

int				main(int argc, char *argv[])
{
	t_args				args;
	t_philos			philos;
	t_log				log;
	pthread_t			watcher;

	if (argc < 5 || argc > 6 || parse_args(&args, argc, argv) == 1)
		return (error_msg("Usage: ./philo_one 2 200 100 100"));
	if (init_sem(&args, &log))
		return (error_msg("unable to create sem_t"));
	if (spawn_philos(&args, &philos) != 0)
		return (error_msg("Unable to spawn philos"));
	watcher = create_watcher(&args);
	awake_philos(&philos);
	sem_wait(args.end);
	kill_philos(&philos);
	delete_philos(&philos);
	pthread_join(watcher, NULL);
	close_sem(&args);
	return (0);
}
