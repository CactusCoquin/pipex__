/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderozie <sderozie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 21:29:51 by sderozie          #+#    #+#             */
/*   Updated: 2023/05/04 11:07:28 by sderozie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

size_t	ft_strlcat(char *dst, const char *src, size_t destsize)
{
	unsigned int	i;
	size_t			dstlen;
	size_t			srclen;

	if (!destsize)
		return (0);
	i = 0;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if ((dstlen >= destsize))
		return (srclen + destsize);
	while (src[i] != '\0' && i + dstlen < destsize - 1)
	{
		dst[i + dstlen] = src[i];
		i++;
	}
	dst[i + dstlen] = '\0';
	return (dstlen + srclen);
}
