/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderozie <sderozie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:43:47 by sderozie          #+#    #+#             */
/*   Updated: 2023/05/04 11:07:36 by sderozie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static size_t	ft_strlen_total(char const *s1, char const *s2)
{
	size_t	i;
	size_t	total_len;

	i = 0;
	total_len = 0;
	while (s1[i] != '\0')
	{
		total_len++;
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		total_len++;
		i++;
	}
	total_len += 1;
	return (total_len);
}

static char	*ft_strcat(char *dst, const char *append, const char *append2)
{
	size_t	i;
	size_t	i2;

	if (!append || !dst || !append2)
		return (NULL);
	i = 0;
	while (append[i] != '\0')
	{
		dst[i] = append[i];
		i++;
	}
	i2 = 0;
	while (append2[i2] != '\0')
	{
		dst[i + i2] = append2[i2];
		i2++;
	}
	dst[i + i2] = '\0';
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen_total(s1, s2);
	dst = (char *) malloc(sizeof(char) * len);
	if (!dst)
		return (NULL);
	ft_strcat(dst, s1, s2);
	return (dst);
}
