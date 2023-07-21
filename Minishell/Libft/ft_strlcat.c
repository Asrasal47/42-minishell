/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 12:21:24 by arasal            #+#    #+#             */
/*   Updated: 2022/04/10 01:16:06 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*strlcat() appends string src to the end of dst. It will append at most
dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate, unless 
dstsize is 0 or the original dst string was longer than dstsize (in practice
this should not happen as it means that either dstsize is incorrect or that
dst is not a proper string) strlcat() function returns the total length of 
the string it tried to create*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	j = dst_len;
	if (dstsize < dst_len)
		return (dstsize + src_len);
	while ((src[i] != '\0') && (dstsize > j)
		&& (i < dstsize - dst_len - 1))
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	if (dstsize - j >= 1)
		dst[j] = '\0';
	return (dst_len + src_len);
}
