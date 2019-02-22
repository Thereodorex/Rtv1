/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 17:55:49 by jcorwin           #+#    #+#             */
/*   Updated: 2019/02/22 15:46:07 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		get_line(int fd, char **line, t_file *file)
{
	char	*end;

	if ((end = ft_strchr(file->buf[fd], '\n')))
		*end = '\0';
	if (!(*line = ft_strdup(file->buf[fd])))
		return (-1);
	while (file->len[fd] && !end)
	{
		if ((file->len[fd] = read(fd, file->buf[fd], BUFF_SIZE)) == -1)
			return (-1);
		file->buf[fd][file->len[fd]] = '\0';
		if ((end = ft_strchr(file->buf[fd], '\n')))
			*end = '\0';
		if (!(*line = ft_rejoin(*line, file->buf[fd])))
			return (-1);
	}
	end ? ft_strcpy(file->buf[fd], end + 1) :
			ft_bzero(file->buf[fd], BUFF_SIZE);
	if (!end && !(**line))
		ft_strdel(line);
	return (*line ? 1 : 0);
}

int				get_next_line(const int fd, char **line)
{
	int				res;
	static t_file	file;

	*line = NULL;
	file.len[fd] = BUFF_SIZE;
	if (fd < 0 || !line)
		return (-1);
	res = get_line(fd, line, &file);
	if (res == -1)
	{
		if (*line)
			free(*line);
		return (-1);
	}
	return (res);
}
