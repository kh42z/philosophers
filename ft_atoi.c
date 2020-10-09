static int	is_space(char c)
{
	if (c == '\n' || c == '\r' || c == '\v' || c == '\f'
		|| c == '\t' || c == ' ')
		return (1);
	return (0);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int			ft_atoi(const char *nptr)
{
	int i;
	int sign;
	int result;

	i = 0;
	sign = 1;
	while (nptr[i] && is_space(nptr[i]) == 1)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (nptr[i] && ft_isdigit(nptr[i]) == 1)
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result * sign);
}