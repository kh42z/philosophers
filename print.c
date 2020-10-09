#include <unistd.h>
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
	char 			print[128];

	t = number_size(usec);
	c = t;
	while (t > 0)
	{
		print[c - t] = ((usec / power10(t)) % 10) + 48;
		--t;
	}
	print[c] = '\0';
	write(1, print, c);
}

void 	print_timestamp(struct timeval *t)
{
	print_number(t->tv_sec);
	write(STDOUT_FILENO, ":", 1);
	print_number(t->tv_usec / 1000);
}

void 	print_current_timestamp()
{
	struct timeval timeval;
	gettimeofday(&timeval, NULL);
	print_timestamp(&timeval);
}

void	print_diff(t_philo *this){

	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	long c = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	long p = this->started_at.tv_sec * 1000 + this->started_at.tv_usec / 1000;

	write(STDOUT_FILENO, "DIFF: ", 6);
	print_number(c - p);
	write(STDOUT_FILENO, "\n", 1);

}

