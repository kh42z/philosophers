#include "philo.h"

void 	*watcher(void *a)
{
	t_args	*args;
	size_t	i;

	args = (t_args *)a;
	i = args->nb_of_philos;
	while (i > 0)
	{
		sem_wait(args->done);
		i--;
	}
	sem_post(args->end);
	return (NULL);
}

void 	create_watcher(t_args *args)
{
	pthread_t			pid;
	int 				err;

	err = pthread_create(&pid, NULL, watcher, args);
	if (err != 0)
		write(STDERR_FILENO, "Unable to create watcher\n", 26);
}

