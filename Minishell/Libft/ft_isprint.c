/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:40:40 by arasal            #+#    #+#             */
/*   Updated: 2022/04/10 01:08:58 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The isprint() function tests for any printing character, including spac.
The isprint() function returns zero if the character tests false and returns 
non-zero if the character tests true.*/
int	ft_isprint(int c)
{
	if ((c >= 32) && (c < 127))
		return (1);
	else
		return (0);
}
