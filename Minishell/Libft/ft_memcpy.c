/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:35:41 by arasal            #+#    #+#             */
/*   Updated: 2022/04/11 00:06:31 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*The memcpy() function copies n bytes from memory area src to memory area 
dst. If dst and src overlap, behavior is undefined. Applications in which 
dst and srcmight overlap should use memmove(3) instead. The memcpy() 
function returns the original value of dst.*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (!dst)
		return (NULL);
	while (++i < n)
		*(char *)(dst + i) = *(char *)(src + i);
	return (dst);
}
