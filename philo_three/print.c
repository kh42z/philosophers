/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterrail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:46:04 by tterrail          #+#    #+#             */
/*   Updated: 2020/10/12 16:46:04 by tterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t		power10(size_t power)
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

static size_t		number_size(suseconds_t usec)
{
	suseconds_t		copy;
	size_t			t;

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

void				print_number(suseconds_t usec)
{
	size_t			t;
	size_t			c;
	static char		buff[1024];

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

void				print_unprotected(t_philo *this, char *s)
{
	size_t		i;

	i = 0;
	while (s[i])
		i++;
	print_number(get_time_ms() - this->started_at);
	print_number(this->id);
	write(STDOUT_FILENO, s, i);
}


void				print_log(t_philo *this, char *s)
{
	sem_wait(this->args.log);
	print_unprotected(this, s);
	sem_post(this->args.log);
}

