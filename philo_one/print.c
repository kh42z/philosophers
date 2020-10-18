/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tterrail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 10:26:40 by tterrail          #+#    #+#             */
/*   Updated: 2020/10/18 10:26:40 by tterrail         ###   ########.fr       */
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

void				add_number(t_log *log, suseconds_t usec)
{
	size_t			t;
	size_t			c;

	t = number_size(usec);
	if (t + log->cursor >= BUFFER_SIZE)
		t = BUFFER_SIZE - (log->cursor + 1);
	c = t;
	while (t > 0)
	{
		log->b1[log->cursor + c - t] = ((usec / power10(t)) % 10) + 48;
		--t;
	}
	log->b1[log->cursor + c] = ' ';
	log->cursor += c + 1;
}

void				add_str(t_log *log, char *s)
{
	size_t		i;

	i = 0;
	while (s[i])
	{
		log->b1[log->cursor] = s[i];
		i++;
		log->cursor++;
	}
}
