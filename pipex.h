/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:17:51 by craimond          #+#    #+#             */
/*   Updated: 2023/12/18 20:09:51 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

# define BUFFER_SIZE 10

struct s_buffers
{
	int		*fds;
	char	*buf;
	char	*tot;
	char	**str_array;
	char	**cmd_args;
	char	*cmd_path;
	char	*path;
};

extern struct s_buffers	buffers;
extern char 			**environ;

void	error(char id);
char	**ft_split(char *s, char c);
void	free_matrix(char **matrix);
char	*strjoin(char *s1, char *s2);
char	*find_cmd(char *path, char *cmd);
char	ft_strncmp(char *s1, char *s2, unsigned int n);

#endif