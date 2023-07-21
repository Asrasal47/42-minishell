/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 23:56:30 by arasal            #+#    #+#             */
/*   Updated: 2022/12/28 10:35:21 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates (with malloc(3)) and returns an array of strings obtained by 
splitting ’s’ using the character ’c’ as a delimiter. The array must end 
with a NULL pointer.*/
static char	*ft_temptrim(char const *s, char c)
{
	char	*temp;
	char	*sub;

	sub = (char *)malloc(sizeof(char) * 2);
	if (!sub)
		return (NULL);
	sub[0] = c;
	sub[1] = '\0';
	temp = ft_strtrim(s, sub);
	if (!temp)
		return (NULL);
	free(sub);
	return (temp);
}

static	size_t	ft_wordcounter(char *temp, char c)
{
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	while (temp[i] != '\0')
	{
		if (temp[i] == c && temp[i + 1] != c)
		{	
			j++;
		}
		i++;
	}
	return (j);
}

static char	**ft_retallocate(char *temp, char **ret, char c, size_t i)
{
	char	*sub;
	size_t	k;

	k = 0;
	while (temp[i] != '\0')
	{
		if (temp[i] == c)
		{
			ret[k++] = ft_substr(temp, 0, i);
			while (temp[i + 1] == c)
				i++;
			sub = ft_substr(temp, (unsigned int)i + 1, ft_strlen(temp) - i);
			free(temp);
			temp = ft_strdup(sub);
			free(sub);
			i = -1;
		}
		i++;
	}
	ret[k] = ft_strdup(temp);
	ret[k + 1] = NULL;
	free(temp);
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	*temp;
	char	**ret;

	i = 0;
	if (!s)
		return (NULL);
	temp = ft_temptrim(s, c);
	if (!temp)
		return (NULL);
	if (temp[0] == '\0')
	{
		ret = (char **)malloc(sizeof(char *) * 1);
		if (!ret)
			return (NULL);
		ret[0] = NULL;
		free(temp);
		return (ret);
	}
	ret = (char **)malloc(sizeof(char *) * (ft_wordcounter(temp, c) + 2));
	ret = ft_retallocate(temp, ret, c, i);
	return (ret);
}
