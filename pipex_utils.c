/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:37:37 by craimond          #+#    #+#             */
/*   Updated: 2023/12/22 11:23:37 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_strcat(char *dest, char *src);
static int	ft_strlen(char *str);
static void	free_matrix(char **matrix);

void	quit(char *msg, unsigned short len)
{
	unsigned short	i;
	int				real_errno;

	real_errno = errno;
	if (msg && errno == 0)
		(void)(write(2, "Error: ", 8) + write(2, msg, len));
	else if (!msg && errno != 0)
		perror("Error");
	free_matrix(buffers.str_array);
	free_matrix(buffers.cmd_args);
	free_matrix(buffers.processes);
	free(buffers.cmd_path);
	i = -1;
	if (buffers.fds)
		while (++i < 4)
			if (buffers.fds[i] != -1)
				close(buffers.fds[i]);
	exit(real_errno);
}

char	check_error(t_pcs process) //implementare una hash table
{
	unsigned short	i;
	unsigned short	len;
	int				valid_code;
	char			*cmd;
	char			*valid_exit[2] = {"grep 1", "awk 2,33"}; //except for 0

	len = -1;
	while (process.cmd[i] != ' ')
		len++;
	process.cmd[len] = '\0';
	i = -1;
	while (++i < 2)
	{
		if (ft_strncmp(process.cmd, valid_exit[i], len) == 0)
		{
			valid_exit[i] += len + 1;
			valid_code = 0;
			while (valid_code != process.exit_status && valid_exit[i])
			{
				valid_code = ft_atoi(valid_exit[i]);
				valid_exit[i] += ft_nbrlen(valid_code) + 1;
			}
			if (valid_code != process.exit_status)
				errno = (WTERMSIG(process.exit_status) + 128) * WIFSIGNALED(process.exit_status) + WEXITSTATUS(process.exit_status) * !WIFSIGNALED(process.exit_status);	
		}
	}
	return (errno != 0);
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

static void	free_matrix(char **matrix)
{
	char	**start;

	if (!matrix)
		return ;
	start = matrix;
	while (*matrix)
		free(*matrix++);
	free(start);
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
