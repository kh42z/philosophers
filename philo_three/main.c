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

int				init_sem(t_args *args)
{
	sem_unlink(SEM_LOG);
	sem_unlink(SEM_END);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_DONE);
	args->forks = sem_open(SEM_FORKS, O_CREAT, 0660, args->nb_of_philos);
	args->log = sem_open(SEM_LOG, O_CREAT, 0660, 1);
	args->end = sem_open(SEM_END, O_CREAT, 0660, 0);
	args->done = sem_open(SEM_DONE, O_CREAT, 0660, 0);
	if (args->forks == SEM_FAILED || args->end == SEM_FAILED ||
		args->log == SEM_FAILED || args->done == SEM_FAILED)
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

void 			close_sem(t_args *args)
{
	sem_close(args->end);
	sem_close(args->log);
	sem_close(args->done);
	sem_close(args->forks);
}

int				main(int argc, char *argv[])
{
	t_args				args;
	t_philos			philos;
	pthread_t 			watcher;

	if (argc < 5 || argc > 6 || parse_args(&args, argc, argv) == 1)
		return (error_msg("Usage: ./philo_two 4 200 10 10\n"));
	if (init_sem(&args) != 0)
		return (error_msg("Unable to create sem\n"));
	if (spawn_philos(&args, &philos) != 0)
		return (error_msg("Unable to malloc\n"));
	watcher = create_watcher(&args);
	awake_philos(&philos);
	sem_wait(args.end);
	kill_philos(&philos);
	delete_philos(&philos);
	pthread_join(watcher, NULL);
	close_sem(&args);
	return (0);
}
