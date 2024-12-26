#include "../Include/minishell.h"

int	is_number(int nb)
{
	if (nb >= '0' && nb <= '9')
		return (1);
	return (0);
}

int	only_number(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
		if (!is_number(s[i++]))
			return (0);
	return (1);
}

int	is_long(char *argv)
{
	if (my_strlen(argv) > 20
		|| my_atoll(argv) > LONG_MAX
		|| my_atoll(argv) < LONG_MIN)
		return (0);
	return (1);
}

long long	my_atoll(const char *nptr)
{
	long long	nb;
	int			mult;

	nb = 0;
	mult = 1;
	while ((*nptr > 8 && *nptr < 14) || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
		mult = -mult;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb = (nb * 10) + (*nptr - '0');
		nptr++;
	}
	return (nb * mult);
}
