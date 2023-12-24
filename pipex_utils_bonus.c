/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:37:37 by craimond          #+#    #+#             */
/*   Updated: 2023/12/24 14:36:26 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_here_doc(int fds[], char **argv, int argc)
{
	char	*content;
	char	*limiter;
	char	*tmp;
	char	len;

	fds[0] = open(".here_doc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fds[0] == -1)
		quit(5, NULL, 0);
	limiter = *argv;
	len = ft_strlen(limiter);
	content = NULL;
    tmp = get_next_line(0);
	while (tmp && ft_strncmp(tmp, limiter, len + 1) != 0)
	{
   	 	content = ft_strjoin(content, tmp);
   		free(tmp);
    	tmp = get_next_line(0);
	}
	if (tmp && content)
		write(fds[0], content, ft_strlen(content) - 1);
	free(tmp);
	free(content);
	if (!tmp)
		quit(6, "invalid here_doc", 17);
	fds[1] = open(argv[argc - 2], O_WRONLY | O_CREAT | O_APPEND, 0644);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newstr;
	int		i;
	int		n;

	i = -1;
	newstr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!newstr)
		quit(14, "failed to allocate memory", 26);
	while (s1 && s1[++i] != '\0')
		newstr[i] = s1[i];
	free(s1);
	n = i + (!s1);
	i = -1;
	while (s2[++i] != '\0')
		newstr[n + i] = s2[i];
	newstr[n + i] = '\0';
	return (newstr);
}
