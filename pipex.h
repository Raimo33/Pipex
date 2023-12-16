/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:17:51 by craimond          #+#    #+#             */
/*   Updated: 2023/12/16 17:15:58 by craimond         ###   ########.fr       */
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
	char	**cmd_args_child;
	char	**cmd_args_parent;
	char	*cmd_path_child;
	char	*cmd_path_parent;
	char	*path_child;
	char	*path_parent;
	char	*full_input;
};

extern struct s_buffers	buffers;
extern char 			**environ;

void	error(void);
char	**split(char *str, char sep);
void	free_matrix(char **matrix);
char	*strjoin(char *s1, char *s2);
char	*ft_read_all(int fds);
char	*find_cmd(char *path, char *cmd);
char	ft_strncmp(char *s1, char *s2, unsigned int n);

#endif