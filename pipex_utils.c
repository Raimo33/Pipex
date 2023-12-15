/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:37:37 by craimond          #+#    #+#             */
/*   Updated: 2023/12/15 15:46:52 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	ft_strcmp(char *s1, char *s2);

void	error(void)
{
	//tutte le free
	perror(strerror(errno));
	exit(errno);
}

// void	ft_cut(char **argv, char *stop)
// {
// 	char			**new_argv;
// 	unsigned short	i;

// 	i = 0;
// 	while (ft_strcmp(argv[i++], stop))
// 		;
// 	new_argv = malloc(i);
// 	buffers.new_argv = new_argv;
// 	if (!new_argv)
// 		error();
// 	new_argv[i] = NULL;
// 	while (--i)
// 		new_argv[i] = argv[i];
// 	return (new_argv);
// }

char	**split(char *str, char sep)
{
	char			**new_argv;
	unsigned short	i;
	unsigned short	j;
	unsigned short	n_words;
	unsigned short	n_chars;

	i = -1;
	n_words = 1;
	while (str[++i])
		if (str[i] == sep)
			n_words++;
	new_argv = malloc((n_words + 1) * sizeof(char *));
	if (!new_argv)
		error();
	new_argv[n_words] = NULL;
	while (--n_words)
	{
		j = 0;
		n_chars = 0;
		while(str[--i] != sep)
			n_chars++;
		new_argv[n_words] = malloc((n_chars + 1) * sizeof(char));
		if (!new_argv[n_words])
		{
			while (n_words--)
				free(new_argv[n_words]);
			free(new_argv);
			error();
		}
		while (str[i + j])
			new_argv[n_words][j] = str[i + j++];
		new_argv[n_words][j] = '\0';
	}
	return (new_argv);
}

char	*strjoin(char *s1, char *s2)
{
	unsigned int	len1;
	unsigned int	len2;
	char			*start;
	char			*new_str;

	len1 = 0;
	len2 = 0;
	while (s1[len1])
		len1++;
	while (s2[len2])
		len2++;
	new_str = malloc((len1 + len2 + 1) * sizeof(char));
	start = new_str;
	while (*s1)
		*new_str++ = *s1++;
	while (*s2)
		*new_str++ = *s2++;
	*new_str = '\0';
	return (start);
}

char	*ft_read_all(int fds)
{
	char			*buf;
	char			*tot;
	char			*tmp;
	unsigned int	i;
	unsigned int	j;

	j = 1;
	tmp = NULL;
	while (1)
	{
		if (read(fds, buf, 0) == -1)
			error();
		buf = malloc(BUFFER_SIZE);
		buffers.buf = buf;
		if (!buf)
			error();
		if (!read(fds, buf, BUFFER_SIZE))
			break ;
		tmp = tot;
		tot = malloc(BUFFER_SIZE * j++ + 1);
		if (!tot)
			error();
		buffers.tot = tot;
		i = -1;
		while(tmp && tmp[++i])
			tot[i] = tmp[i];
		free(tmp);
		i--;
		while (buf[++i])
			tot[i] = buf[i];
		tot[i] = '\0';
		free(buf);
	}
	free(buf);
	return (tot);
}

// static char	ft_strcmp(char *s1, char *s2)
// {
// 	while (s1 && s2 && *s1++ == *s2++)
// 		;
// 	return (*s1 - *s2);
// }
