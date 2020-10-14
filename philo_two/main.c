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

int				init_sem(t_args *args, t_end *end)
{
	memset(end, 0, sizeof(t_end));
	sem_unlink(SEM_LOG);
	sem_unlink(SEM_END);
	sem_unlink(SEM_FORKS);
	args->forks = sem_open(SEM_FORKS, O_CREAT, 0660, args->nb_of_philos);
	args->log = sem_open(SEM_LOG, O_CREAT, 0660, 1);
	end->tid = sem_open(SEM_END, O_CREAT, 0660, 1);
	args->end = end;
	if (args->forks == SEM_FAILED || end->tid == SEM_FAILED ||
	args->log == SEM_FAILED)
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

	if (argc < 5 || argc > 6 || parse_args(&args, argc, argv) == 1)
		return (error_msg("Usage: ./philo_two 4 200 10 10\n"));
	if (init_sem(&args, &end) != 0)
		return (error_msg("Unable to create sem\n"));
	if (spawn_philos(&args, &philos) != 0)
		return (error_msg("Unable to malloc\n"));
	awake_philos(&philos);
	wait_philos(&philos);
	delete_philos(&philos);
	sem_close(end.tid);
	sem_close(args.forks);
	sem_close(args.log);
	return (0);
}
