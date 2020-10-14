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

pthread_t			create_watcher(t_args *args)
{
	pthread_t			pid;
	int 				err;

	err = pthread_create(&pid, NULL, watcher, args);
	if (err != 0)
		write(STDERR_FILENO, "Unable to create watcher\n", 26);
	return (pid);
}

static void 		announce_death(t_philo *this)
{
	sem_wait(this->args.log);
	print_unprotected(this, "died\n");
	sem_post(this->args.end);
}

void		*is_he_dead(void *philo)
{
	t_philo	*this;

	this = (t_philo*)philo;
	while (1)
	{
		sem_wait(this->eating);
		if (this->args.nb_of_must_eat == 0)
			break;
		if (is_dead(this) == 1)
		{
			announce_death(this);
			sem_post(this->eating);
			break ;
		}
		sem_post(this->eating);
		usleep(1);
	}
	return (NULL);
}

