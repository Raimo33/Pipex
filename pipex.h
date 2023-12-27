/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:17:51 by craimond          #+#    #+#             */
/*   Updated: 2023/12/27 15:11:07 by craimond         ###   ########.fr       */
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

struct s_buffers
{
	int		*fds;
	char	**str_array;
	char	**cmd_args;
	char	*cmd_path;
};

extern struct s_buffers	g_buffers;

void	init(int fds[]);
void	handle_command(int fds[], char **argv, char *path, char **envp);
void	handle_pipe(int fds[], char **argv, char *path, char **envp);
void	wait_child(void);
char	*get_path(char **envp);
char	*find_cmd(char *path, char *cmd);
char	**ft_split(char *s, char c);
void	quit(unsigned char id, char *msg, unsigned short len);
char	ft_strncmp(char *s1, char *s2, int n);
char	*ft_strncpy(char *dest, char *src, int n);
char	*ft_strcat(char *dest, char *src);
int		ft_strlen(char *str);
void	free_matrix(char **matrix);

#endif