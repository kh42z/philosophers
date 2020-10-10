#include "philo.h"

void 				delete_forks(t_forks *forks)
{
	while(forks->size > 0)
	{
		free(forks->fork[forks->size - 1]);
		forks->size--;
	}
	free(forks);
}

t_forks 			*new_forks(unsigned int number) {
	t_forks *forks;

	forks = malloc(sizeof(t_forks));
	if (forks == NULL)
		return (NULL);
	forks->size = 0;
	forks->fork = malloc(sizeof(t_fork *) * number);
	if (forks == NULL)
	{
		free(forks);
		return NULL;
	}
	while (forks->size < number)
	{
		forks->fork[forks->size] = malloc(sizeof(t_fork));
		if (forks->fork[forks->size] == NULL)
		{
			delete_forks(forks);
			return (NULL);
		}
		forks->size++;
	}
	forks->size++;
	return (forks);
}
