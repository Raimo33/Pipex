/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:37:37 by craimond          #+#    #+#             */
/*   Updated: 2023/12/19 20:11:55 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_strncpy(char *dest, char *src, int n);
static char	*ft_strcat(char *dest, char *src);
static int	ft_strlen(char *str);

void	quit(char id)
{
	if (id != 0)
		perror("Error");

	//la logica della variabile globale buffers non funziona perce' anche essa viene duplicata tra parent e child, quindi non e' possibile liberarla dal parent

	// free(buffers.buf);
	// free(buffers.tot);
	// free_matrix(buffers.str_array);
	// free_matrix(buffers.cmd_args);
	// free(buffers.cmd_path);
	// free(buffers.path);
	if (buffers.fds)
	{
		close(buffers.fds[0]);
		close(buffers.fds[1]);
		close(buffers.fds[2]);
		close(buffers.fds[3]);
	}
	exit(id);
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
	unsigned int	g;
	unsigned int	len;

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
		quit(10);
	buffers.str_array = str_array;
	str_array[n_words] = NULL;
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
			quit(11);
		ft_strncpy(str_array[g], s, len);
		str_array[g][len] = '\0';
		s += len;
	}
	return (str_array);
}

void	free_matrix(char **matrix)
{
	char	**start;

	start = matrix;
	while (matrix && *matrix)
		free(*matrix++);
	free(start);
}

static char	*ft_strncpy(char *dest, char *src, int n)
{
	unsigned int	i;

	i = -1;
	while (src[++i] && n-- > 0)
		dest[i] = src[i];
	while (n-- > 0)
		dest[i++] = '\0';
	return (dest);
}

static char	*ft_strcat(char *dest, char *src)
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

static int	ft_strlen(char *str)
{
	char	*start;

	start = str;
	while (*str++ != '\0')
		;
	return (str - start);
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

// char	*strjoin(char *s1, char *s2)
// {
// 	unsigned int	len1;
// 	unsigned int	len2;
// 	char			*start;
// 	char			*new_str;

// 	len1 = 0;
// 	len2 = 0;
// 	while (s1[len1])
// 		len1++;
// 	while (s2[len2])
// 		len2++;
// 	new_str = malloc((len1 + len2 + 1) * sizeof(char));
// 	start = new_str;
// 	while (*s1)
// 		*new_str++ = *s1++;
// 	while (*s2)
// 		*new_str++ = *s2++;
// 	*new_str = '\0';
// 	return (start);
// }

// void	ft_cut(char **argv, char *stop)
// {
// 	char			**new_argv;
// 	unsigned short	i;
//
// 	i = 0;
// 	while (ft_strcmp(argv[i++], stop))
// 		;
// 	new_argv = malloc(i);
// 	buffers.new_argv = new_argv;
// 	if (!new_argv)
// 		quit();
// 	new_argv[i] = NULL;
// 	while (--i)
// 		new_argv[i] = argv[i];
// 	return (new_argv);
// }

// char	*ft_read_all(int fd)
// {
// 	char			*buf;
// 	char			*tot;
// 	char			*tmp;
// 	unsigned int	i;
// 	unsigned int	j;
//
// 	j = 1;
// 	tot = NULL;
// 	buf = NULL;
// 	while (1)
// 	{
// 		if (read(fd, buf, 0) == -1)
// 			quit();
// 		buf = malloc(BUFFER_SIZE + 1);
// 		buffers.buf = buf;
// 		if (!buf)
// 			quit();
// 		if (read(fd, buf, BUFFER_SIZE) == 0)
// 			break ;
// 		buf[BUFFER_SIZE] = '\0';
// 		tmp = tot;
// 		tot = malloc(BUFFER_SIZE * j++ + 1);
// 		if (!tot)
// 			quit();
// 		buffers.tot = tot;
// 		i = -1;
// 		while(tmp && tmp[++i])
// 			tot[i] = tmp[i];
// 		free(tmp);
// 		while (*buf)
// 			tot[i++] = *buf++;
// 		tot[i] = '\0';
// 		free(buf - BUFFER_SIZE - 1);
// 	}
// 	free(buf);
// 	return (tot);
// }
