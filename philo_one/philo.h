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
	THINKING,
	EATING,
	SLEEPING,
};

typedef struct			s_args {
	unsigned int		nb_of_philos;
	suseconds_t 		tt_die;
	suseconds_t 		tt_eat;
	suseconds_t 		tt_sleep;
	long				nb_of_must_eat;
}						t_args;

typedef struct			s_fork {
	pthread_mutex_t 	tid;
}						t_fork;

typedef struct 			s_end {
	pthread_mutex_t 	tid;
	int 				is_over;
}						t_end;

typedef struct			s_philo {
	unsigned int 		id;
	enum philo_actions 	action;
	long 				started_at;
	long 				ate_at;
	t_args				args;
	t_fork				*left;
	t_fork				*right;
	pthread_mutex_t 	*print;
	t_end			 	*end;
	pthread_t			pid;
}						t_philo;

typedef struct			s_forks {
	t_fork 				**items;
	size_t 				size;
}						t_forks;

typedef struct			s_philos {
	t_philo 			**philo;
	size_t 				size;
}						t_philos;


int 	is_dead(t_philo *this);
void 	*do_next(void *v);

long 	get_time_ms();
void 	print_log(t_philo *this, char *s);
int		parse_args(t_args  *args, int argc, char *argv[]);
void 	print_unprotected(t_philo *this, char *s);

void				wait_philos(t_philos *p);
int					awake_philos(t_philos *p);
int 				new_forks(t_forks *forks, unsigned int number);
int		 			spawn_philos(t_args *args, t_philos *philos, t_forks *forks, pthread_mutex_t *mutex, t_end *end);
void 				delete_forks(t_forks *forks);
void		 		delete_philos(t_philos *philos);
#endif //PHILO_PHILO_H
