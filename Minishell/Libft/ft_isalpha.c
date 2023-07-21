/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:23:49 by arasal            #+#    #+#             */
/*   Updated: 2022/04/10 00:02:47 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The isalpha() function tests for any character for which isupper(3) or 
islower(3) is true. The isalpha() function returns zero if the character 
tests false and returns non-zero if the character tests true.*/
int	ft_isalpha(int c)
{
	if (((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122)))
		return (1);
	else
		return (0);
}
