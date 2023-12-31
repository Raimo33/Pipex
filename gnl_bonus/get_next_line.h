/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:27:55 by craimond          #+#    #+#             */
/*   Updated: 2023/12/27 15:26:16 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef B_SIZE
#  define B_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

char	*get_next_line(int fd);
char	*get_single_line(char *str);
char	*f_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);
char	*ft_calloc(size_t nmemb, size_t size);
char	*free_and_null(char *to_free, char **to_null);
void	quit(unsigned char id, char *msg, unsigned short len);

#endif
