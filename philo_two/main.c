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

int				init_sem(t_args *args, t_end *end, sem_t *log_mutex,
				sem_t **forks)
{
	memset(end, 0, sizeof(t_end));
	sem_unlink(SEM_LOG);
	sem_unlink(SEM_END);
	sem_unlink(SEM_FORKS);
	*forks = sem_open(SEM_FORKS, O_CREAT, 0660, args->nb_of_philos);
	log_mutex = sem_open(SEM_LOG, O_CREAT, 0660, 1);
	end->tid = sem_open(SEM_END, O_CREAT, 0660, 1);
	args->log = log_mutex;
	args->end = end;
	if (*forks == SEM_FAILED || end->tid == SEM_FAILED ||
	log_mutex == SEM_FAILED)
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
	t_end				end;
	sem_t				*forks;
	sem_t				log_mutex;

	if (argc < 5 || argc > 6 || parse_args(&args, argc, argv) == 1)
		return (error_msg("Usage: ./philo_two 4 200 10 10"));
	if (init_sem(&args, &end, &log_mutex, &forks) != 0)
		return (error_msg("Unable to create sem"));
	if (spawn_philos(&args, &philos, forks) != 0)
		return (error_msg("Unable to malloc"));
	awake_philos(&philos);
	wait_philos(&philos);
	delete_philos(&philos);
	sem_close(end.tid);
	sem_close(forks);
	sem_close(&log_mutex);
	return (0);
}
