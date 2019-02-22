/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 13:05:59 by jcorwin           #+#    #+#             */
/*   Updated: 2019/02/02 17:17:38 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include "libft.h"

# define BUFF_SIZE 32

typedef struct	s_file
{
	int				len[1000];
	char			buf[1000][BUFF_SIZE + 1];
}				t_file;

int				get_next_line(const int fd, char **line);

#endif
