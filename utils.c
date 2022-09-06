/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 21:36:39 by mclerico          #+#    #+#             */
/*   Updated: 2022/09/06 12:18:22 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		l1;
	int		l2;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	l1 = (int)ft_strlen(s1);
	l2 = (int)ft_strlen(s2);
	i = 0;
	join = malloc((l1 + l2 + 1) * sizeof(char));
	if (join == NULL)
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[i - l1])
	{
		join[i] = s2[i - l1];
		i++;
	}
	join[i] = 0;
	return (join);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	if (n == 0)
		return (0);
	while (n != 0)
	{
		if (*s1 != *s2++)
			return (*(unsigned char *)s1 - *(unsigned char *)(s2 - 1));
		if (*s1++ == 0)
			break ;
		n--;
	}
	return (0);
}

static int	ft_nwords(char const *s, char c)
{
	int	fletter;
	int	i;
	int	count;

	fletter = -1;
	i = 0;
	count = 0;
	while (s[i])
	{
		if (fletter == -1 && s[i] != c)
			fletter = i;
		else if (fletter != -1 && s[i] == c)
		{
			fletter = -1;
			count++;
		}
		i++;
	}
	if (fletter != -1)
		count++;
	return (count);
}

static char	*ft_copy(char const *s, char c, int *i)
{
	int		l;
	int		cont;
	char	*str;

	l = 0;
	cont = 0;
	while (s[(*i) + cont] && s[(*i) + cont] != c)
		cont++;
	str = (char *)malloc(cont + 1);
	if (!str)
		return (NULL);
	while (l < cont)
		str[l++] = s[(*i)++];
	str[l] = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		i;
	int		k;
	int		n;

	if (!s)
		return (NULL);
	i = 0;
	n = 0;
	k = 0;
	n = ft_nwords(s, c);
	p = (char **)malloc ((n + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	while (s[i] && k < n)
	{
		if (s[i] != c)
			p[k++] = ft_copy(s, c, &i);
		else
			i++;
	}
	p[k] = NULL;
	return (p);
}
