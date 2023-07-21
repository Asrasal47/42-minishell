/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 22:14:30 by arasal            #+#    #+#             */
/*   Updated: 2023/03/03 15:18:22 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	t_list_gnl		f;
	static char		*rest[OPEN_MAX];

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	init_rest(&f, fd, rest);
	f.number = BUFFER_SIZE;
	while (f.number && f.number % BUFFER_SIZE == 0
		&& (!(ft_strchr_x(f.line, '\n'))))
	{
		f.number = read(fd, f.buff, BUFFER_SIZE);
		if ((f.number == 0 && (!*f.line)) || f.number == -1)
		{
			if (f.line)
				free(f.line);
			return (NULL);
		}
		f.buff[f.number] = '\0';
		f.line = ft_strjoin_x(f.line, f.buff);
	}
	ft_saverest(&f, fd, rest);
	ft_returnline(&f);
	return (f.line);
}

void	ft_saverest(t_list_gnl *f, int fd, char *rest[OPEN_MAX])
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (f->line == NULL)
		return ;
	while (f->line[j] != '\0')
		j++;
	while (f->line[i] != '\n' && f->line[i] != '\0')
		i++;
	if (i != j)
		rest[fd] = ft_substr_x(f->line, i + 1, j - (i + 1));
	else
		rest[fd] = ft_strdup_x("");
}

void	init_rest(t_list_gnl *f, int fd, char *rest[OPEN_MAX])
{
	if (rest[fd])
	{
		f->line = ft_strdup_x(rest[fd]);
		free(rest[fd]);
		rest[fd] = NULL;
	}
	else
		f->line = ft_strdup_x("");
}

void	ft_returnline(t_list_gnl *f)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	if (f->line == NULL)
		return ;
	while (f->line[j] != '\0')
		j++;
	while (f->line[i] != '\n' && f->line[i] != '\0')
		i++;
	if (i != j)
	{
		ret = ft_substr_x(f->line, 0, i + 1);
		free (f->line);
		f->line = ft_strdup_x(ret);
		free (ret);
	}
}
