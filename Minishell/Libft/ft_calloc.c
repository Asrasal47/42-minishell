/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 21:05:10 by arasal            #+#    #+#             */
/*   Updated: 2022/04/13 16:00:18 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The calloc() function contiguously allocates enough space for count 
objects that are size bytes of memory each and returns a pointer to 
the allocated memory. The allocated memory is filled with bytes of 
value zero.*/
void	*ft_calloc(size_t count, size_t size)
{
	char	*str;

	str = malloc(count * size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, (count * size));
	return ((void *)str);
}
