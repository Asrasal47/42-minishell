/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:00:22 by arasal            #+#    #+#             */
/*   Updated: 2023/04/14 17:31:02 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	variable_substr_verify(t_var_exp *t, int start, int j, char **s)
{
	t->temp1 = ft_substr(*s, 0, start);
	if (t->xo == 1)
		t->temp2 = ft_substr(*s, start, j - 1);
	else
		t->temp2 = ft_substr(*s, start, j - start);
	if (t->xo == 1)
		t->temp3 = ft_strdup("\n");
	else
		t->temp3 = ft_strdup((*s) + j);
	t->temp = ft_strjoin(t->temp2, "=");
}

static void	variable_substr(t_minishell *m, t_var_exp *t, int *j, char **s)
{
	int		start;
	char	*tmp;

	start = (*j)++;
	if ((*s)[(*j)] != '?')
	{
		while ((*s)[(*j)] && (*s)[(*j)] != ' ' && (*s)[(*j)] != '$'
			&& (*s)[(*j)] != '\'' && (*s)[(*j)] != '\"'
			&& (*s)[(*j)] != '?')
		{
			tmp = ft_substr(*s, start, (*j) - start + 1);
			if (!ft_strnstr(m->line, tmp, ft_strlen(m->line)) && t->xo != 1)
			{
				free(tmp);
				break ;
			}
			free(tmp);
			(*j)++;
		}
	}
	else
		(*j)++;
	variable_substr_verify(t, start, (*j), s);
}

static void	env_var_exp(t_minishell *m, t_var_exp *t, int *j, char **s)
{
	int	i;

	i = -1;
	while (m->e->env_save[++i])
	{
		if (!ft_strncmp(t->temp + 1, m->e->env_save[i],
				ft_strlen(t->temp + 1)) && t->temp[0] == '$')
		{
			free(*s);
			free(t->temp2);
			t->temp2 = ft_strjoin(m->e->env_save[i] + ft_strlen(t->temp + 1),
					t->temp3);
			*s = ft_strjoin(t->temp1, t->temp2);
			free(t->temp);
			break ;
		}
	}
	if (t->temp && t->temp[0] == '$' && ft_isalpha(t->temp[1])
		&& !m->e->env_save[i])
	{
		free(*s);
		*s = ft_strjoin(t->temp1, t->temp3);
		*j -= (ft_strlen(t->temp) - 1);
		free(t->temp);
	}
}

char	*ft_variable_expansion(char *s, t_minishell *m, int x)
{
	t_var_exp	t;
	int			j;

	if (!s)
		return (NULL);
	var_exp_init(&t, x);
	j = -1;
	while (s[++j])
	{
		if (s[j] == '$' && s[j + 1] && s[j + 1] != ' ')
		{
			variable_substr(m, &t, &j, &s);
			if (ft_strchr(t.temp1, '\"') && ft_strchr(t.temp3, '\"'))
			{
				free_var_temp(&t, 0);
				j++;
				continue ;
			}
			else
				env_var_exp(m, &t, &j, &s);
			free_var_temp(&t, 1);
			j--;
		}
	}
	return (s);
}
