#include "philo.h"

void 				delete_forks(t_forks *forks)
{
	while(forks->size > 0)
	{
		free(forks->items[forks->size - 1]);
		forks->size--;
	}
}

int		new_forks(t_forks *f, unsigned int number)
{
	f->size = 0;
	f->items = malloc(sizeof(t_fork *) * number);
	if (f->items == NULL)
		return (1);
	while (f->size < number)
	{
		f->items[f->size] = malloc(sizeof(t_fork));
		if (f->items[f->size] == NULL)
		{
			delete_forks(f);
			return (1);
		}
		f->size++;
	}
	return (0);
}
