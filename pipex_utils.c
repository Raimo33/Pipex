/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 13:57:18 by craimond          #+#    #+#             */
/*   Updated: 2023/12/24 15:37:41 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**fill_matrix(unsigned int n_words, char *s, char c, char **str_array);

char *get_path(char **envp)
{
	while (envp && *envp)
		if (ft_strncmp(*envp++, "PATH=", 5) == 0)
			return (*(envp - 1) + 5);
	quit(13, "PATH not found", 15);
	return (NULL);
}

char	*find_cmd(char *path, char *cmd)
{
	char			**dirs;
	char			*full_path;
	unsigned int	i;
	unsigned int	size;

	dirs = ft_split(path, ':');
	full_path = NULL;
	i = -1;
	while (dirs[++i])
	{
		size = ft_strlen(dirs[i]) + ft_strlen(cmd) + 2;
		full_path = malloc(size * sizeof(char));
		if (!full_path)
			break ;
		ft_strncpy(full_path, dirs[i], size);
		ft_strcat(full_path, "/");
		ft_strcat(full_path, cmd);
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
	}
	free_matrix(dirs);
	return (full_path);
}

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
		quit(14, "failed to allocate memory", 26);
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
			quit(15, "failed to allocate memory", 26);
		ft_strncpy(str_array[g], s, len);
		str_array[g][len] = '\0';
		s += len;
	}
    return (str_array);
}

void	quit(unsigned char id, char *msg, unsigned short len)
{
	unsigned short	i;

	if (msg && *msg)
		(void)(write(2, "Error: ", 8) + write(2, msg, len));
	else if (!msg && id != 0)
		perror("Error");
	free_matrix(buffers.str_array);
	//free_matrix(buffers.cmd_args);
	free(buffers.cmd_path);
	i = -1;
	if (buffers.fds)
		while (++i < 4)
			if (buffers.fds[i] != -1)
				close(buffers.fds[i]);
	unlink(".here_doc.tmp");
	exit(id);
}
