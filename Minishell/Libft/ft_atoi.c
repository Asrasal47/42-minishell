/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:13:24 by arasal            #+#    #+#             */
/*   Updated: 2022/04/10 01:06:50 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The atoi function works by removing all possible whitespace 
characters similar to the isspace function—until it encounters 
the first non-whitespace character. After the first non-whitespace, 
it assigns an optional sign (positive or negative). Next, it 
parses all the possible base-10 values until it encounters a 
non-numerical character. This could be a null-terminating character. 
Finally, it interprets the values into their corresponding integer type.*/
int	ft_atoi(const char *str)
{
	int	res;
	int	i;
	int	j;

	res = 0;
	i = 0;
	j = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '-' || (str[i] == '+'))
	{
		if (str[i] == '-' && j == 1)
			j = -1;
		if (str[i + 1] == '-' || str[i + 1] == '+')
			return (res);
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * j);
}
