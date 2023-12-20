/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:56:23 by craimond          #+#    #+#             */
/*   Updated: 2023/12/20 15:16:16 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**fill_matrix(unsigned int n_words, char *s, char c, char **str_array);

char	**ft_split(char *s, char c)
{
	char			**str_array;
	unsigned int	n_words;
	unsigned int	i;

	if (!s || *s == '\0')
		return (NULL);
	i = -1;
	n_words = 0;
	if (s[0] != c && s[0] != '\0')
		n_words = 1;
	while (s[++i + 1] != '\0')
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			n_words++;
	str_array = malloc(sizeof(char *) * (n_words + 1));
	if (!str_array)
		quit("failed to allocate memory", 25);
	buffers.str_array = str_array;
	str_array[n_words] = NULL;
	return (fill_matrix(n_words, s, c, str_array));
}

static char	**fill_matrix(unsigned int n_words, char *s, char c, char **str_array)
{
	unsigned int	g;
	unsigned int	len;

	g = -1;
	while (++g < n_words)
	{
		len = 0;
		while (*s == c)
			s++;
		while (s[len] != c && s[len] != '\0')
			len++;
		str_array[g] = malloc(sizeof(char) * (len + 1));
		if (!str_array[g])
			quit("failed to allocate memory", 25);
		ft_strncpy(str_array[g], s, len);
		str_array[g][len] = '\0';
		s += len;
	}
    return (str_array);
}

char	ft_strncmp(char *s1, char *s2, int n)
{
	while (n-- > 1 && (*s1 == *s2) && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	return ((n > 0) * (*s1 - *s2));
}

char	*ft_strncpy(char *dest, char *src, int n)
{
	unsigned int	i;

	i = -1;
	while (src[++i] && n-- > 0)
		dest[i] = src[i];
	while (n-- > 0)
		dest[i++] = '\0';
	return (dest);
}
