/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:42:55 by arasal            #+#    #+#             */
/*   Updated: 2023/04/17 14:27:53 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	char_value_assign(char c, int *q, int *l, int p)
{
	*q += 1;
	*l = p;
	return (c);
}

static void	quote_screening(char **w, char *s, int *i, int len)
{
	int	l;
	int	q[2];

	l = 0;
	q[0] = 0;
	q[1] = 0;
	while (s[*i] && *i < len)
	{
		if (s[*i] == '\'' && !(q[1] % 2))
			(*w)[*i] = char_value_assign('0', &q[0], &l, 1);
		else if (s[*i] == '\'' && q[1] % 2)
			(*w)[*i] = char_value_assign('1', &q[0], &l, 1);
		else if (s[*i] == '\"' && q[0] % 2)
			(*w)[*i] = char_value_assign('2', &q[1], &l, 2);
		else if (s[*i] == '\"' && !(q[0] % 2))
			(*w)[*i] = char_value_assign('0', &q[1], &l, 2);
		else if (s[*i] == '$' && s[(*i) + 1] && s[(*i) + 1] == '?'
			&& (!(q[0] % 2) || (l == 1 && q[1] != 0) || q[0] == 0))
			(*w)[(*i)++] = '4';
		else
			(*w)[*i] = '3';
		(*i)++;
	}
}

static void	quote_parsing(char **w, char *s, int len)
{
	int	i;

	i = -1;
	while (s[++i] && i < len)
	{
		if (s[i] == '$' && s[i + 1] && (s[i + 1] == '\'' || s[i + 1] == '\"'))
				(*w)[i] = '0';
		else if (s[i] == '$' && s[i + 1] && s[i + 1] == '?')
		{
			(*w)[i + 1] = '0';
			(*w)[(i++)] = '4';
		}
		else if (s[i] == ' ' && s[i + 1] && s[i + 1] == ' ')
			ft_quotes_fix(w, s, &i);
		else if (s[i] == '\'' || s[i] == '\"')
		{
			quote_screening(w, s, &i, len);
			break ;
		}
		else
			(*w)[i] = '3';
	}
	(*w)[i] = '\0';
}

static void	quote_restructuring(char **w, char **t, char *s, int len)
{
	int		i;
	int		j;
	int		l;
	char	*ex;

	i = -1;
	j = 0;
	ex = ft_itoa(g_glob.exit_status);
	while (++i <= len && j <= len)
	{
		l = 0;
		if ((*w)[i] == '1')
			(*t)[j++] = '\'';
		else if ((*w)[i] == '2')
			(*t)[j++] = '\"';
		else if ((*w)[i] == '3')
			(*t)[j++] = s[i];
		else if ((*w)[i] == '4')
			while (ex[l])
				(*t)[j++] = ex[l++];
	}
	(*t)[j] = '\0';
	free(ex);
}

char	*ft_quotes(char *s)
{
	char	*t;
	int		i[2];
	int		len;
	int		l;
	char	*w;

	i[0] = 0;
	i[1] = 0;
	l = 0;
	len = ft_strlen(s);
	t = (char *)malloc(sizeof(char) * len + 1);
	w = (char *)malloc(sizeof(char) * len + 1);
	quote_parsing(&w, s, len);
	i[0] = 0;
	quote_restructuring(&w, &t, s, len);
	free(w);
	return (t);
}
