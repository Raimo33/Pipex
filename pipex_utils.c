/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 13:57:18 by craimond          #+#    #+#             */
/*   Updated: 2023/12/27 15:06:03 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**fill_matrix(unsigned int n_words, char *s, char c, char **matrix);

char	*get_path(char **envp)
{
	while (envp && *envp)
		if (ft_strncmp(*envp++, "PATH=", 5) == 0)
			return (*(envp - 1) + 5);
	quit(7, "PATH not found", 15);
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
		quit(8, "failed to allocate memory", 26);
	g_buffers.str_array = str_array;
	str_array[n_words] = NULL;
	return (fill_matrix(n_words, s, c, str_array));
}

static char	**fill_matrix(unsigned int n_words, char *s, char c, char **matrix)
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
		matrix[g] = malloc(sizeof(char) * (len + 1));
		if (!matrix[g])
			quit(9, "failed to allocate memory", 26);
		ft_strncpy(matrix[g], s, len);
		matrix[g][len] = '\0';
		s += len;
	}
	g_buffers.str_array = NULL;
	return (matrix);
}

void	quit(unsigned char id, char *msg, unsigned short len)
{
	unsigned short	i;

	if (msg && *msg)
		(void)(write(2, "Error: ", 8) + write(2, msg, len));
	else if (!msg && id != 0)
		perror("Error");
	free_matrix(g_buffers.str_array);
	free_matrix(g_buffers.cmd_args);
	free(g_buffers.cmd_path);
	i = -1;
	if (g_buffers.fds)
		while (++i < 4)
			if (g_buffers.fds[i] != -1)
				close(g_buffers.fds[i]);
	unlink(".here_doc.tmp");
	exit(id);
}
