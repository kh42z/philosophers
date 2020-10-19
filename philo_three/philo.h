/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterrail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 10:56:43 by tterrail          #+#    #+#             */
/*   Updated: 2020/10/15 10:56:43 by tterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_PHILO_H
# define PHILO_PHILO_H
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

# define BUFFER_SIZE 128
# define SEM_FORKS "/philo_forks"
# define SEM_END "/philo_end"
# define SEM_LOG "/philo_log"
# define SEM_DONE "/philo_done"

enum					e_actions {
	THINKING,
	EATING,
	SLEEPING,
};

typedef struct			s_log {
	sem_t				*tid;
	char				b1[BUFFER_SIZE];
	size_t				cursor;
}						t_log;

typedef struct			s_args {
	unsigned int		nb_of_philos;
	suseconds_t			tt_die;
	suseconds_t			tt_eat;
	suseconds_t			tt_sleep;
	long				nb_of_must_eat;
	t_log				*log;
	sem_t				*forks;
	sem_t				*end;
	sem_t				*done;
}						t_args;

typedef struct			s_philo {
	unsigned int		id;
	enum e_actions		action;
	long				started_at;
	long				ate_at;
	t_args				args;
	sem_t				*started;
	sem_t				*eating;
	sem_t				*forks;
	t_log				*log;
	pthread_t			pid;
	pthread_t			watcher;
}						t_philo;

typedef struct			s_philos {
	t_philo				**philo;
	size_t				size;
}						t_philos;

void					*is_he_dead(void *this);
int						is_dead(t_philo *this);
void					*do_next(void *v);

void					kill_philos(t_philos *p);
void					dump(t_log *this);
long					get_time_ms();
long					get_time_us();
pthread_t				create_watcher(t_args *args);
int						parse_args(t_args *args, int argc, char *argv[]);
void					add_str(t_log *log, char *s);
void					add_number(t_log *log, suseconds_t usec);
void					wait_philos(t_philos *p, t_args *args);
int						awake_philos(t_philos *p);
suseconds_t				min(suseconds_t i1, suseconds_t i2);
int						spawn_philos(t_args *args, t_philos *philos);
int						add(t_log *this, t_philo *p, char *s);
void					log_death(t_log *this, t_philo *p);
void					delete_philos(t_philos *philos);
t_philo					*new_philo(t_args *args, suseconds_t started_at,
						unsigned int i);
void					empty_buffer(t_log *this);
#endif
