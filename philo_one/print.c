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

void 	print_number(suseconds_t usec)
{
	size_t			t;
	size_t 			c;
	static char 			buff[1024];

	t = number_size(usec);
	if (t > 1022)
		t = 1022;
	c = t;
	while (t > 0)
	{
		buff[c - t] = ((usec / power10(t)) % 10) + 48;
		--t;
	}
	buff[c] = ' ';
	buff[c + 1] = '\0';
	write(STDOUT_FILENO, buff, c + 1);
}



void 	print_unprotected(t_philo *this, char *s)
{
	size_t 					i;

	i = 0;
	while (s[i])
		i++;
	pthread_mutex_lock(this->print);
	print_number(get_time_ms() - this->started_at);
	print_number(this->id);
	write(STDOUT_FILENO, s, i);
	pthread_mutex_unlock(this->print);
}


void 	print_log(t_philo *this, char *s)
{

	int 					is_over;

	pthread_mutex_lock(&this->end->tid);
	is_over = this->end->is_over;
	pthread_mutex_unlock(&this->end->tid);
	if (is_over == 1)
		return ;
	print_unprotected(this, s);
}

