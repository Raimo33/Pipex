/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 14:21:52 by craimond          #+#    #+#             */
/*   Updated: 2023/12/24 14:36:19 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*ft_strcat(char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = -1;
	while (src[++j] != '\0')
		dest[i + j] = src[j];
	dest[i + j] = '\0';
	return (dest);
}

int	ft_strlen(char *str)
{
	char	*start;

	if (!str)
		return (0);
	start = str;
	while (*str++ != '\0')
		;
	return (str - start - 1);
}

void	free_matrix(char **matrix)
{
	char	**start;

	if (!matrix)
		return ;
	start = matrix;
	while (*matrix)
		free(*matrix++);
	free(start);
}
