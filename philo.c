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
		print_log(this, " has taken a left fork\n");
		pthread_mutex_lock(&this->right->tid);
		print_log(this, " has taken a right fork\n");
		this->ate_at = get_time_ms();
		print_log(this, " is eating\n");
		if ((err = usleep(this->args.tt_eat * 1000)) != 0)
			print_log(this, " USLEEP FAILED");
		pthread_mutex_unlock(&this->right->tid);
		pthread_mutex_unlock(&this->left->tid);
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
	int 	over;

	over = 0;
	this = (t_philo*)v;
	this->ate_at = get_time_ms();
	while (is_dead(this) == 0 && this->args.nb_of_must_eat != 0)  {
		pthread_mutex_lock(&this->end->tid);
		if (this->end->is_over == 1)
			over = 1;
		pthread_mutex_unlock(&this->end->tid);
		if (over == 1)
			break ;
		this->action++;
		if (this->action > 2)
			this->action = 0;
		do_stuff(this);
	}
	if (over == 0)
	{
		pthread_mutex_lock(&this->end->tid);
		this->end->is_over = 1;
		pthread_mutex_unlock(&this->end->tid);
		if (this->args.nb_of_must_eat != 0)
			print_log(this, " is dead\n");
	}
	return (this);
}

t_philo 		*new_philo(t_args *args, t_forks *forks, pthread_mutex_t *mutex, t_end *end, unsigned int i)
{
	t_philo *p;

	p = malloc(sizeof(t_philo));
	if (p == NULL)
		return (NULL);
	memset(p, 0, sizeof(t_philo));
	p->print = mutex;
	p->end = end;
	p->args = *args;
	p->id = i;
	p->action = THINKING;
	p->left = forks->items[i];
	p->started_at = get_time_ms();
	if (i + 1 == args->nb_of_philos)
		p->right = forks->items[0];
	else
		p->right = forks->items[i + 1];
	return (p);
}

int 			spawn_philos(t_args *args, t_philos *philos, t_forks *forks, pthread_mutex_t *mutex, t_end *end)
{
	int i;

	philos->size = 0;
	philos->philo = malloc(sizeof(t_philo*) * args->nb_of_philos);
	if (!philos->philo)
		return (-1);
	while (philos->size < args->nb_of_philos)
	{
		i = philos->size;
		philos->philo[i] = new_philo(args, forks, mutex, end, i);
		if (philos->philo[i] == NULL) {
			delete_philos(philos);
			return (-1);
		}
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
	free(philos->philo);
}