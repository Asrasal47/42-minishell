/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:14:20 by arasal            #+#    #+#             */
/*   Updated: 2022/04/10 00:11:20 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates (with malloc(3)) and returns a string representing the integer 
received as an argument. Negative numbers must be handled. It returns
the string representing the integer or NULL if the allocation fails.*/
static int	ft_sign(long long n)
{
	int	si;

	si = 1;
	if (n < 0)
	{
		si = -1;
	}
	return (si);
}

static int	ft_counter(long long n)
{
	int	k;

	k = 0;
	if (n == 0)
		k = 1;
	if (n < 0)
	{
		n = -n;
		k = 1;
	}
	while (n > 0)
	{
		n = n / 10;
		k++;
	}
	return (k);
}

char	*ft_itoa(int n2)
{
	long long	n;
	char		*str;
	int			i;
	int			sign;

	n = (long long)n2;
	sign = ft_sign(n);
	i = ft_counter(n);
	if (sign < 0)
		n = -n;
	str = (char *)malloc(i + 1);
	if (!str)
		return (0);
	str[i] = '\0';
	while (i - 1 > 0)
	{
		str[i-- - 1] = n % 10 + '0';
		n = n / 10;
	}
	if (sign < 0)
		str[i - 1] = '-';
	else
		str[i - 1] = n + '0';
	return (str);
}
