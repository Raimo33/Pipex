/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:27:37 by craimond          #+#    #+#             */
/*   Updated: 2023/12/23 15:15:36 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_single_line(char *str)
{
	char	*new_str;
	int		i;

	i = 0;
	if (!str || *str == '\0')
		return (NULL);
	new_str = malloc(f_sl(str) + (str[f_sl(str) - 1] == '\n'));
	if (!new_str)
		return (NULL);
	while (str[++i] != '\0' && str[i] != '\n')
		new_str[i - 1] = str[i];
	if (i <= f_sl(str) && str[i] == '\n')
	{
		new_str[i - 1] = str[i];
		i++;
	}
	new_str[i - 1] = '\0';
	return (new_str);
}

char	*f_strjoin(char *s1, char *s2)
{
	char	*newstr;
	int		i;
	int		s1_len;
	int		s2_len;

	if (s1 && *s1 == -42)
		s1++;
	s1_len = f_sl(s1) + 1;
	s2_len = f_sl(s2);
	i = 0;
	newstr = malloc((s1_len + s2_len + 1));
	if (newstr)
		newstr[0] = -42;
	while (newstr && ++i < s1_len && s1)
		newstr[i] = s1[i - 1];
	i = -1;
	while (newstr && ++i < s2_len && s2)
		newstr[s1_len + i] = s2[i];
	if (newstr)
		newstr[s1_len + i] = '\0';
	free(s2);
	while (s1 && *s1 != -42)
		s1--;
	free(s1);
	return (newstr);
}

char	*ft_calloc(size_t nmemb, size_t size)
{
	char	*arr;
	int		n;

	if (nmemb != 0 && size > ULONG_MAX / nmemb)
		return (NULL);
	n = nmemb * size;
	arr = malloc(n);
	while (arr && n-- > 0)
		arr[n] = '\0';
	return (arr);
}

char	*free_and_null(char *to_free, char **to_null)
{
	free(to_free);
	*to_null = NULL;
	return (NULL);
}
