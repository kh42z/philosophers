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

# define BUFFER_SIZE 2048
enum					e_actions {
	THINKING,
	EATING,
	SLEEPING,
};

typedef struct			s_end {
	pthread_mutex_t		tid;
	int					is_over;
}						t_end;

typedef struct 			s_log {
	pthread_mutex_t 	tid;
	char 				b1[BUFFER_SIZE];
	size_t 				cursor;
	int 				sim_over;
}						t_log;

typedef struct			s_args {
	unsigned int		nb_of_philos;
	suseconds_t			tt_die;
	suseconds_t			tt_eat;
	suseconds_t			tt_sleep;
	long				nb_of_must_eat;
	t_log				*log;
}						t_args;

typedef struct			s_fork {
	pthread_mutex_t		tid;
}						t_fork;


typedef struct			s_philo {
	unsigned int		id;
	enum e_actions		action;
	long				started_at;
	long				ate_at;
	t_args				args;
	t_fork				*left;
	t_fork				*right;
	pthread_mutex_t 	started;
	pthread_mutex_t		eating;
	t_log				*log;
	pthread_t			pid;
	pthread_t			watcher;
}						t_philo;

typedef struct			s_forks {
	t_fork				**items;
	size_t				size;
}						t_forks;

typedef struct			s_philos {
	t_philo				**philo;
	size_t				size;
}						t_philos;

void					*is_he_dead(void *this);
int						is_dead(t_philo *this);
void					*do_next(void *v);

long					get_time_ms();
void					print_log(t_philo *this, char *s);
int						parse_args(t_args *args, int argc, char *argv[]);
void					print_unprotected(t_philo *this, char *s);

void					wait_philos(t_philos *p);
int						awake_philos(t_philos *p);
int						new_forks(t_forks *forks, unsigned int number);
suseconds_t 			min(suseconds_t i1, suseconds_t i2);
int						spawn_philos(t_args *args, t_philos *philos,
						t_forks *forks);
void					delete_forks(t_forks *forks);
int					 	add(t_log *this, t_philo *p, char *s);
void					dump(t_log *this);
void 					log_death(t_log *this, t_philo *p);
void					delete_philos(t_philos *philos);
t_philo					*new_philo(t_args *args, t_forks *forks, unsigned int i);
#endif
