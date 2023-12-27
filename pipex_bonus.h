/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:44:00 by craimond          #+#    #+#             */
/*   Updated: 2023/12/27 15:09:56 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"
# include "gnl_bonus/get_next_line.h"

void	handle_here_doc(int fds[], char **argv, int argc);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);

#endif