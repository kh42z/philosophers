#include "philo.h"

int 	is_dead(t_philo *this) {
	struct timeval current_time;

	gettimeofday(&current_time, NULL);

	long c = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	long p = this->started_at.tv_sec * 1000 + this->started_at.tv_usec / 1000;

	if (c - p > this->args.tt_die)
		return (1);
	return (0);
}

void 	do_stuff(t_philo *this) {
	struct timeval	current;
	int 			err;
	gettimeofday(&current, NULL);
	print_timestamp(&current);
	write(STDOUT_FILENO, " ", 1);
	print_number((suseconds_t)this->id);
	if (this->action == EATING) {
		this->started_at = current;
		write(STDOUT_FILENO, " is eating ", 11);
		if ((err = usleep(this->args.tt_eat * 1000)) != 0)
			printf("ERRROR %s\n", strerror(err));
		print_current_timestamp();
		write(STDOUT_FILENO, "\n", 1);
		if (this->args.nb_of_must_eat > 0)
			this->args.nb_of_must_eat--;
	}
	if (this->action == SLEEPING) {
		write(STDOUT_FILENO, " is sleeping\n", 13);
		if ((err = usleep(this->args.tt_sleep * 1000)) != 0)
			printf("ERRROR %s\n", strerror(err));
		print_current_timestamp();
	}
	if (this->action == THINKING) {
		write(STDOUT_FILENO, " is thinking\n", 13);
	}
}

void 	*do_next(void *v) {

	t_philo *this;
	this = (t_philo*)v;
	gettimeofday(&this->started_at, NULL);
	while (is_dead(this) == 0) {
		print_diff(this);
		this->action++;
		if (this->action > 2)
			this->action = 0;
		do_stuff(this);
	}
	print_diff(this);
	print_current_timestamp();
	write(STDOUT_FILENO, " ", 1);
	print_number(this->id);
	write(STDOUT_FILENO, " just died\n", 11);
	return (this);
}


