/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sderozie <sderozie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:17:07 by sderozie          #+#    #+#             */
/*   Updated: 2023/05/04 12:55:15 by sderozie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static unsigned int	ft_check_sep(char c, char c2)
{
	if (c == c2)
		return (1);
	else
		return (0);
}

static unsigned int	ft_total_words(char const *s, char c)
{
	unsigned int	count;

	count = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && ft_check_sep(*s, c))
			s++;
		if (*s != '\0' && !ft_check_sep(*s, c))
			count++;
		while (*s != '\0' && !ft_check_sep(*s, c))
			s++;
	}
	return (count);
}

static char	*ft_words(char const *s, char c)
{
	char	*word;
	size_t	i;

	i = 0;
	while (s[i] != '\0' && !ft_check_sep(s[i], c))
		i++;
	word = (char *) malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && !ft_check_sep(s[i], c))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**ft_free(char **strs, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	i;

	if (!s)
		return (NULL);
	strs = (char **) malloc(sizeof(char *) * (ft_total_words(s, c) + 1));
	if (!strs)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && ft_check_sep(*s, c))
			s++;
		if (*s != '\0' && !ft_check_sep(*s, c))
		{
			strs[i] = ft_words(s, c);
			if (!strs[i])
				return (ft_free(strs, i));
			i++;
		}
		while (*s != '\0' && !ft_check_sep(*s, c))
			s++;
	}
	strs[i] = 0;
	return (strs);
}
