/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:17:51 by craimond          #+#    #+#             */
/*   Updated: 2023/12/14 19:56:12 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>

# define BUFFER_SIZE 100

struct s_buffers
{
	char	*out;
	char	*buf;
	char	*tot;
};

extern struct s_buffers buffers;

void	error(void);

#endif