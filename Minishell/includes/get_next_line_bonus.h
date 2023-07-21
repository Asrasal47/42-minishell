/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 22:14:56 by arasal            #+#    #+#             */
/*   Updated: 2023/03/03 15:20:32 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "../Libft/libft.h"

typedef struct s_list_gnl
{
	char		buff[BUFFER_SIZE + 1];
	char		*line;
	long long	number;
}					t_list_gnl;

char	*get_next_line(int fd);
char	*ft_substr_x(char const *s, unsigned int start, size_t len);
char	*ft_strjoin_x(char const *s1, char const *s2);
char	*ft_strchr_x(const char *s, int c);
char	*ft_strdup_x(const char *s1);
size_t	ft_strlen(const char *s);
void	ft_returnline(t_list_gnl *f);
void	ft_saverest(t_list_gnl *f, int fd, char *rest[OPEN_MAX]);
void	init_rest(t_list_gnl *f, int fd, char *rest[OPEN_MAX]);
#endif