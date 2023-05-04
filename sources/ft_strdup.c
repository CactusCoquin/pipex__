/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderozie <sderozie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:30:00 by sderozie          #+#    #+#             */
/*   Updated: 2023/05/04 11:07:40 by sderozie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_strdup(const char *s)
{
	char	*p;
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(s);
	p = (char *) malloc(sizeof(char) * (srclen + 1));
	i = 0;
	if (!p)
		return (0);
	while (i < srclen)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
