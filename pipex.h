/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:17:51 by craimond          #+#    #+#             */
/*   Updated: 2023/12/15 15:50:38 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>

# define BUFFER_SIZE 100

struct s_buffers
{
	char	*buf;
	char	*tot;
	char	**cmd_args_child;
	char	**cmd_args_parent;
	char	*path_child;
	char	*path_parent;
	char	*full_input;
};

extern struct s_buffers	buffers;
extern char **environ;

void	error(void);
// void	ft_cut(char **argv, char *stop);
char	**split(char *str, char sep);
char	*strjoin(char *s1, char *s2);
char	*ft_read_all(int fds);


#endif