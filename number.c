#include "minishell.h"

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
	if (s[i] == '-')
		return (0);
	if (s[i] == '+')
		i++;
	while (s[i])
		if (!is_number(s[i++]))
			return (0);
	return (1);
}

int	is_long(char *argv)
{
	if (ft_strlen(argv) > 20
		|| ft_atoll(argv) > LONG_MAX
		|| ft_atoll(argv) < LONG_MIN)
		return (0);
	return (1);
}

long long	ft_atoll(const char *nptr)
{
	long long	nb;
	int		mult;

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

static size_t	house_places(int n)
{
	size_t	places;

	places = 0;
	if (n < 0)
		places++;
	while (n != 0)
	{
		n /= 10;
		places++;
	}
	return (places);
}

char	*ft_itoa(int n)
{
	size_t	size_n;
	char	*new_s;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (!n)
		return (ft_strdup("0"));
	size_n = house_places(n);
	new_s = malloc(sizeof(char) * (size_n + 1));
	if (!new_s)
		return (NULL);
	new_s[size_n--] = '\0';
	if (n < 0)
	{
		new_s[0] = '-';
		n = -n;
	}
	while (n != 0)
	{
		new_s[size_n--] = n % 10 + '0';
		n /= 10;
	}
	return (new_s);
}
