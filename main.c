#include "philo.h"

static void		parse_args(t_args  *args, int argc, char *argv[])
{
	args->nb_of_philos = ft_atoi(argv[1]);
	args->tt_die = (suseconds_t)ft_atoi(argv[2]);
	args->tt_eat = (suseconds_t)ft_atoi(argv[3]);
	args->tt_sleep = (suseconds_t)ft_atoi(argv[4]);
	args->nb_of_must_eat = 0;
	if (argc == 6)
		args->nb_of_must_eat = ft_atoi(argv[5]);
}

int 			spawn_philos(t_args *args, t_philos *philos)
{
	int i;
	int err;

	philos->size = 0;
	philos->philo = malloc(sizeof(t_philo*) * args->nb_of_philos);
	if (!philos->philo)
		return (-1);
	while (philos->size < args->nb_of_philos)
	{
		i = philos->size;
		philos->philo[i] = malloc(sizeof(t_philo));
		if (philos->philo[i] == NULL) {
			return (-1);
		}
		memset(philos->philo[i], 0, sizeof(t_philo));
		philos->philo[i]->args = *args;
		philos->philo[i]->id = i;
		if ((err = pthread_create(&philos->philo[i]->pid, NULL, do_next, philos->philo[i])) != 0)
			return (err);
		philos->size++;
	}
}

int				main(int argc, char *argv[]) {
	t_args args;
	t_philos philos;
	if (argc < 5 || argc > 6)
		return (1);
	parse_args(&args, argc, argv);
	spawn_philos(&args, &philos);
	pthread_join(philos.philo[0]->pid, NULL);

	return (0);
}
