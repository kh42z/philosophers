#include "philo.h"

int				main(int argc, char *argv[]) {
	t_args			args;
	t_philos		philos;
	t_forks			forks;
	t_end			end;

	memset(&end, 0, sizeof(t_end));
	pthread_mutex_init(&end.tid, NULL);
	pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER;

	if (argc < 5 || argc > 6 || parse_args(&args, argc, argv) == 1)
	{
		write(STDERR_FILENO, "Invalid arguments\n", 19);
		return (1);
	}
	if (new_forks(&forks, args.nb_of_philos) != 0)
		return (1);
	if (spawn_philos(&args, &philos, &forks, &mutex, &end) != 0)
	{
		delete_forks(&forks);
		return (1);
	}
	if (awake_philos(&philos) == 0)
		wait_philos(&philos);
	delete_forks(&forks	);
	delete_philos(&philos);
	return (0);
}