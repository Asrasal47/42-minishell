/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 00:51:59 by abouthib          #+#    #+#             */
/*   Updated: 2023/04/14 17:07:13 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_arrlen(char **s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	c1;
	unsigned char	c2;
	size_t			i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		c1 = (unsigned char) *s1++;
		c2 = (unsigned char) *s2++;
		if (c1 != c2)
			return (c1 - c2);
		if (c1 == '\0')
			return (0);
	}
	return (0);
}

char	*ft_strlower(char *str)
{
	size_t	n;

	n = 0;
	if (!str)
		return (NULL);
	while (str[n])
	{
		str[n] = ft_tolower((int) str[n]);
		n++;
	}
	return (str);
}

static int	ft_stradd_init(char ***p, char *temp)
{
	(*p) = malloc(sizeof(char *) * 2);
	if (!(*p))
		return (1);
	(*p)[0] = ft_strdup(temp);
	(*p)[1] = NULL;
	return (0);
}

int	ft_stradd(char *temp, char ***tokenized)
{
	int		i;
	char	**p;

	i = 0;
	if ((*tokenized) == NULL)
	{
		if (ft_stradd_init(&p, temp))
			return (1);
	}
	else
	{
		while ((*tokenized)[i])
			i++;
		p = malloc(sizeof(char *) * (i + 2));
		if (!p)
			return (1);
		i = -1;
		while ((*tokenized)[++i])
			p[i] = ft_strdup((*tokenized)[i]);
		p[i] = ft_strdup(temp);
		p[i + 1] = NULL;
		free_s((*tokenized));
	}
	*tokenized = p;
	return (0);
}
