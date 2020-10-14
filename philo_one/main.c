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

void			init_mutex(t_args *args, t_end *end)
{
	memset(end, 0, sizeof(t_end));
	pthread_mutex_init(&args->log, NULL);
	pthread_mutex_init(&end->tid, NULL);
	args->end = end;
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
	t_end				end;

	if (argc < 5 || argc > 6 || parse_args(&args, argc, argv) == 1)
		return error_msg("Usage: ./philo_one 2 200 100 100");
	init_mutex(&args, &end);
	if (new_forks(&forks, args.nb_of_philos) != 0)
		return error_msg("Unable to create forks");
	if (spawn_philos(&args, &philos, &forks) != 0)
	{
		delete_forks(&forks);
		return error_msg("Unable to spawn philos");
	}
	awake_philos(&philos);
	wait_philos(&philos);
	delete_forks(&forks);
	delete_philos(&philos);
	return (0);
}
