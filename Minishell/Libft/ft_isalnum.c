/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:43:04 by arasal            #+#    #+#             */
/*   Updated: 2022/04/10 00:15:27 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The isalnum() function tests for any character for which isalpha(3) or 
isdigit(3) is true. The isalnum() function returns zero if the character 
tests false and returns non-zero if the character tests true.*/
int	ft_isalnum(int c)
{
	if (((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122)))
		return (1);
	else if ((c >= 48) && (c <= 57))
		return (1);
	else
		return (0);
}
