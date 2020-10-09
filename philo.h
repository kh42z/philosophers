#ifndef PHILO_PHILO_H
#define PHILO_PHILO_H
#include <sys/time.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

enum philo_actions {
	EATING,
	SLEEPING,
	THINKING,
};

typedef struct			s_args {
	unsigned int		nb_of_philos;
	suseconds_t 		tt_die;
	suseconds_t 		tt_eat;
	suseconds_t 		tt_sleep;
	unsigned int		nb_of_must_eat;
}						t_args;

typedef struct			s_philo {
	unsigned int 		id;
	enum philo_actions 	action;
	struct timeval		started_at;
	t_args				args;
	pthread_t			pid;
}						t_philo;

typedef struct			s_philos {
	t_philo 			**philo;
	size_t 				size;
}						t_philos;


int 	is_dead(t_philo *this);
void 	*do_next(void *v);


int		ft_atoi(const char *nptr);

void 	print_number(suseconds_t usec);
void 	print_current_timestamp();
void 	print_timestamp(struct timeval *t);
void	print_diff(t_philo *this);

#endif //PHILO_PHILO_H
