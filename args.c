#include "philo.h"

static int	isdigit(int c) {
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

suseconds_t 		eatos(char *str, int *err)
{
	size_t			i;
	suseconds_t		arg;

	i = 0;
	*err = 0;
	arg = 0;
	while (str[i])
	{
		if (isdigit(str[i]) == 0)
		{
			*err = 1;
			return (0);
		}
		arg = arg * 10 + (str[i] - '0');
		++i;
	}
	return (arg);
}

int		parse_args(t_args  *args, int argc, char *argv[])
{
	int err;

	args->nb_of_philos = eatos(argv[1], &err);
	if (err != 0)
		return (1);
	args->tt_die = eatos(argv[2], &err);
	if (err != 0)
		return (1);
	args->tt_eat = eatos(argv[3], &err);
	if (err != 0)
		return (1);
	args->tt_sleep = eatos(argv[4], &err);
	if (err != 0)
		return (1);
	args->nb_of_must_eat = -1;
	if (argc == 6)
		args->nb_of_must_eat = eatos(argv[5], &err);
	if (err != 0)
		return (1);
	return (0);
}
