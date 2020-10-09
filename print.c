#include "philo.h"

static  size_t 		power10(size_t power)
{
	size_t t;

	t = 1;
	while (power > 1)
	{
		t *= 10;
		power--;
	}
	return (t);
}

static size_t 	number_size(suseconds_t usec){
	suseconds_t		copy;
	size_t 			t;

	if (usec == 0)
		return (1);
	copy = usec;
	t = 0;
	while (copy > 0)
	{
		copy /= 10;
		t++;
	}
	return (t);
}

void 	print_number(suseconds_t usec, char *print)
{
	size_t			t;
	size_t 			c;

	t = number_size(usec);
	c = t;
	while (t > 0)
	{
		print[c - t] = ((usec / power10(t)) % 10) + 48;
		--t;
	}
	print[c] = '\0';
	write(STDOUT_FILENO, print, c);
}


void 	print_log(t_philo *this, char *s){
	size_t 					i;
	char 			print[128];

	i = 0;
	while (s[i])
		i++;
	pthread_mutex_lock(this->mutex);
	write(STDOUT_FILENO, "> ", 2);
	print_number(get_time_ms() - this->started_at, &print);
	write(STDOUT_FILENO, " (", 2);
	print_number(this->id, &print);
	write(STDOUT_FILENO, ") ", 2);
	write(STDOUT_FILENO, s, i);
	pthread_mutex_unlock(this->mutex);
}




