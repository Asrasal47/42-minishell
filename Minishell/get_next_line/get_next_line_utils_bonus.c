/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 22:15:29 by arasal            #+#    #+#             */
/*   Updated: 2023/03/03 15:18:33 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line_bonus.h"

char	*ft_substr_x(char const *s, unsigned int start, size_t len)
{
	char			*s2;
	unsigned int	sublen;
	unsigned int	subcount;

	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	sublen = 0;
	while (s[start + sublen] != '\0')
		sublen++;
	if (sublen > (unsigned int)len)
		sublen = (unsigned int)len;
	s2 = (char *)malloc(sublen + 1);
	if (!s2)
		return (NULL);
	subcount = 0;
	while (subcount < sublen)
	{
		s2[subcount] = s[start];
		subcount++;
		start++;
	}
	s2[subcount] = '\0';
	return (s2);
}

char	*ft_strjoin_x(char const *s1, char const *s2)
{
	int		s1len;
	int		s2len;
	int		s3len;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	s3len = 0;
	s3 = (char *)malloc(s1len + s2len + 1);
	if (!s3)
		return (NULL);
	while (s3len < s1len + s2len)
	{
		if (s3len < s1len)
			s3[s3len] = s1[s3len];
		else
			s3[s3len] = s2[s3len - s1len];
		s3len++;
	}
	free ((void *)s1);
	s3[s3len] = '\0';
	return (s3);
}

char	*ft_strchr_x(const char *s, int c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[j] != '\0')
		j++;
	while (i <= j)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

char	*ft_strdup_x(const char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i] != '\0')
		i++;
	s2 = (char *)malloc(i + 1);
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

size_t	ft_strlen_x(const char *s)
{
	size_t	t;

	t = 0;
	if (!s)
		return (0);
	while (s[t] != '\0')
		t++;
	return (t);
}
