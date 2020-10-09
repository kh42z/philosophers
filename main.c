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

int				main(int argc, char *argv[]) {
	t_args args;
	t_philos philos;
	t_forks  *forks;
	pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_unlock(&mutex);
	if (argc < 5 || argc > 6)
		return (1);
	parse_args(&args, argc, argv);
	forks = new_forks(args.nb_of_philos);
	if (forks == NULL)
		return (1);
	if (spawn_philos(&args, &philos, forks, &mutex) != 0){
		delete_forks(forks);
		return (1);
	}
	pthread_join(philos.philo[0]->pid, NULL);
	return (0);
}
