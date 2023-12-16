/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:37:37 by craimond          #+#    #+#             */
/*   Updated: 2023/12/16 18:35:40 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_strcpy(char *dest, char *src);
static char	*ft_strcat(char *dest, char *src);
static int	ft_strlen(char *str);

void	error(void)
{
	//tutte le free
	//tutti i close
	perror("Error");
	exit(errno);
}

char	*find_cmd(char *path, char *cmd)
{
	char	**dirs;
	char	*full_path;

	dirs = split(path, ':');
	full_path = NULL;
	while (*dirs)
	{
		full_path = malloc(ft_strlen(*dirs) + ft_strlen(cmd) + 2);
		if (!full_path)
			break ;
		ft_strcpy(full_path, *dirs);
		ft_strcat(full_path, "/");
		ft_strcat(full_path, cmd);
		if (access(full_path, X_OK) == 0)
			break ;
		free(full_path);
		full_path = NULL;
		dirs++;
	}
	free_matrix(dirs);
	return (full_path);
}

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
			free_matrix(new_argv);
			error();
		}
		while (str[i + j])
		{
			new_argv[n_words][j] = str[i + j];
			j++;
		}
		new_argv[n_words][j] = '\0';
	}
	return (new_argv);
}

void	free_matrix(char **matrix)
{
	while (*matrix)
		free(*matrix++);
	free(matrix);
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

static char	*ft_strcpy(char *dest, char *src)
{
	char	*start;

	start = dest;
	while (*src != '\0')
		*dest++ = *src++;
	*dest = '\0';
	return (start);
}

static char	*ft_strcat(char *dest, char *src)
{
	char	*start;

	start = dest;
	while (*dest != '\0')
		dest++;
	while (*src != '\0')
		*dest++ = *src++;
	*dest = '\0';
	return (start);
}

static int	ft_strlen(char *str)
{
	char *start;

	start = str;
	while (*str++ != '\0')
		;
	return (str - start);
}

char	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	if (n == 0)
		return (0);
	while ((*s1 == *s2) && *s1 && *s2 && n-- > 1)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

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
// 		error();
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
// 			error();
// 		buf = malloc(BUFFER_SIZE + 1);
// 		buffers.buf = buf;
// 		if (!buf)
// 			error();
// 		if (read(fd, buf, BUFFER_SIZE) == 0)
// 			break ;
// 		buf[BUFFER_SIZE] = '\0';
// 		tmp = tot;
// 		tot = malloc(BUFFER_SIZE * j++ + 1);
// 		if (!tot)
// 			error();
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