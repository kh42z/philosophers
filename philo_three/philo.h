#ifndef PHILO_PHILO_H
#define PHILO_PHILO_H
#include <sys/time.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <string.h>
#include <wait.h>

# define SEM_FORKS "/philo_forks"
# define SEM_END "/philo_end"
# define SEM_LOG "/philo_log"
# define SEM_DONE "/philo_done"

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
	sem_t			 	*log;
	sem_t				*forks;
	sem_t			 	*end;
	sem_t				*done;
}						t_args;

typedef struct			s_philo {
	unsigned int 		id;
	enum philo_actions 	action;
	long 				started_at;
	long 				ate_at;
	t_args				args;
	sem_t				*forks;
	sem_t				*eating;
	pthread_t 			watcher;
	pthread_t			pid;
}						t_philo;

typedef struct			s_philos {
	t_philo 			**philo;
	size_t 				size;
}						t_philos;


int 	is_dead(t_philo *this);
void 	*do_next(void *v);
void	*is_he_dead(void *philo);
pthread_t			create_watcher(t_args *args);

long 	get_time_ms();
void 	print_log(t_philo *this, char *s);
int		parse_args(t_args  *args, int argc, char *argv[]);
void 	print_unprotected(t_philo *this, char *s);

void				kill_philos(t_philos *p);
int					awake_philos(t_philos *p);
int					spawn_philos(t_args *args, t_philos *philos);
void		 		delete_philos(t_philos *philos);
t_philo				*new_philo(t_args *args, long started_at, unsigned int i);
#endif //PHILO_PHILO_H
