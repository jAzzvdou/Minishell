/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jazevedo <jazevedo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:37:09 by jazevedo          #+#    #+#             */
/*   Updated: 2024/06/17 09:46:27 by jazevedo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*final;

	final = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!final)
		return (NULL);
	i = -1;
	while (s[++i])
		final[i] = s[i];
	final[i] = '\0';
	return (final);
}

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*new;

	if (!s || n < 1)
		return (NULL);
	new = malloc(sizeof(char) * (n + 1));
	i = -1;
	while (s[++i] && i < n)
		new[i] = s[i];
	while (i < n)
		new[i] = '\0';
	new[i] = '\0';
	return (new);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size_s1;
	char	*new_s;

	if (!set)
		return (ft_strdup(s1));
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	size_s1 = ft_strlen(s1) - 1;
	while (s1[size_s1] && ft_strchr(set, s1[size_s1]))
		size_s1--;
	new_s = ft_substr(s1, 0, size_s1 + 1);
	return (new_s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*new_s;

	new_s = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	while (*s1)
		new_s[i++] = *s1++;
	while (*s2)
		new_s[i++] = *s2++;
	new_s[i] = '\0';
	return (new_s);
}
