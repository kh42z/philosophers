#include "philo.h"

int 	is_dead(t_philo *this)
{
	long c;

	c = get_time_ms();
	if (c - this->ate_at > this->args.tt_die)
		return (1);
	return (0);
}

void 	do_stuff(t_philo *this) {
	int 			err;

	if (this->action == EATING) {
		pthread_mutex_lock(&this->left->tid);
		pthread_mutex_lock(&this->right->tid);
		this->ate_at = get_time_ms();
		print_log(this, " is eating\n");
		if ((err = usleep(this->args.tt_eat * 1000)) != 0)
			printf("ERROR %s\n", strerror(err));
		pthread_mutex_unlock(&this->left->tid);
		pthread_mutex_unlock(&this->right->tid);
		if (this->args.nb_of_must_eat > 0)
			this->args.nb_of_must_eat--;
	}
	if (this->action == SLEEPING) {
		print_log(this, " is sleeping\n");
		if ((err = usleep(this->args.tt_sleep * 1000)) != 0)
			printf("ERRROR %s\n", strerror(err));
	}
	if (this->action == THINKING) {
		print_log(this, " is thinking\n");
	}
}

void 	*do_next(void *v) {

	t_philo *this;
	this = (t_philo*)v;
	this->ate_at = get_time_ms();
	while (is_dead(this) == 0 && this->args.nb_of_must_eat != 0)  {
		this->action++;
		if (this->action > 2)
			this->action = 0;
		do_stuff(this);
	}
	print_log(this, " is dead\n");
	pthread_mutex_lock(&this->end->tid);
	this->end->is_over = 1;
	pthread_mutex_unlock(&this->end->tid);
	return (this);
}

int 			spawn_philos(t_args *args, t_philos *philos, t_forks *forks, pthread_mutex_t *mutex, t_end *end)
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
			delete_philos(philos);
			return (-1);
		}
		memset(philos->philo[i], 0, sizeof(t_philo));
		philos->philo[i]->print = mutex;
		philos->philo[i]->end = end;
		philos->philo[i]->args = *args;
		philos->philo[i]->id = i;
		philos->philo[i]->action = THINKING;
		philos->philo[i]->left = forks->items[i];
		philos->philo[i]->started_at = get_time_ms();
		if (i + 1 == args->nb_of_philos)
			philos->philo[i]->right = forks->items[0];
		else
			philos->philo[i]->right = forks->items[i + 1];
		if ((err = pthread_create(&philos->philo[i]->pid, NULL, do_next, philos->philo[i])) != 0)
			return (err);
		philos->size++;
	}
	return (0);
}

void 		delete_philos(t_philos *philos)
{
	while(philos->size > 0)
	{
		free(philos->philo[philos->size - 1]);
		--philos->size;
	}
}