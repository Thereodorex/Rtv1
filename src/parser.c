/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 14:14:19 by jcorwin           #+#    #+#             */
/*   Updated: 2019/02/21 21:06:06 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		get_plane(t_param *p, int fd, char **line)
{
	char	*word2;
	char	*word3;

	plane_real(p);
	gnl(fd, line);
	while (*line && **line && **line != ' ')
	{
		word2 = get_word(*line);
		word3 = get_word(word2);
		if (*word3 == '0' && *(word3 + 1) == 'x')
			word3 += 2;
		if (!ft_strcmp(*line, "color"))
			p->plane[p->plane_count - 1].color = ft_atoi_base(word3, 16);
		else if (!ft_strcmp(*line, "point"))
			p->plane[p->plane_count - 1].point = get_vec(word3);
		else if (!ft_strcmp(*line, "specular"))
			p->plane[p->plane_count - 1].specular = get_double(word3);
		else if (!ft_strcmp(*line, "normal"))
			p->plane[p->plane_count - 1].norm = get_vec(word3);
		else if (!(**line == '/' && *(*line + 1) == '/'))
			STOP;
		gnl(fd, line);
	}
}

static void		get_cyl(t_param *p, int fd, char **line)
{
	char	*word2;
	char	*word3;

	cyl_real(p);
	gnl(fd, line);
	while (*line && **line && **line != ' ')
	{
		word2 = get_word(*line);
		word3 = get_word(word2);
		if (*word3 == '0' && *(word3 + 1) == 'x')
			word3 += 2;
		if (!ft_strcmp(*line, "color"))
			p->cyl[p->cyl_count - 1].color = ft_atoi_base(word3, 16);
		else if (!ft_strcmp(*line, "center"))
			p->cyl[p->cyl_count - 1].cen = get_vec(word3);
		else if (!ft_strcmp(*line, "radius"))
			p->cyl[p->cyl_count - 1].rad = get_double(word3);
		else if (!ft_strcmp(*line, "specular"))
			p->cyl[p->cyl_count - 1].specular = get_double(word3);
		else if (!ft_strcmp(*line, "direction"))
			p->cyl[p->cyl_count - 1].dir = get_vec(word3);
		else if (!(**line == '/' && *(*line + 1) == '/'))
			STOP;
		gnl(fd, line);
	}
}

static void		get_cone(t_param *p, int fd, char **line)
{
	char	*word2;
	char	*word3;

	con_real(p);
	gnl(fd, line);
	while (*line && **line && **line != ' ')
	{
		word2 = get_word(*line);
		word3 = get_word(word2);
		if (*word3 == '0' && *(word3 + 1) == 'x')
			word3 += 2;
		if (!ft_strcmp(*line, "color"))
			p->con[p->con_count - 1].color = ft_atoi_base(word3, 16);
		else if (!ft_strcmp(*line, "center"))
			p->con[p->con_count - 1].cen = get_vec(word3);
		else if (!ft_strcmp(*line, "cos"))
			p->con[p->con_count - 1].cos = get_double(word3);
		else if (!ft_strcmp(*line, "specular"))
			p->con[p->con_count - 1].specular = get_double(word3);
		else if (!ft_strcmp(*line, "direction"))
			p->con[p->con_count - 1].dir = get_vec(word3);
		else if (!(**line == '/' && *(*line + 1) == '/'))
			STOP;
		gnl(fd, line);
	}
}

static void		get_sphere(t_param *p, int fd, char **line)
{
	char	*word2;
	char	*word3;

	sp_real(p);
	gnl(fd, line);
	while (*line && **line && **line != ' ')
	{
		word2 = get_word(*line);
		word3 = get_word(word2);
		if (*word3 == '0' && *(word3 + 1) == 'x')
			word3 += 2;
		if (!ft_strcmp(*line, "color"))
			p->sp[p->sp_count - 1].color = ft_atoi_base(word3, 16);
		else if (!ft_strcmp(*line, "center"))
			p->sp[p->sp_count - 1].cen = get_vec(word3);
		else if (!ft_strcmp(*line, "radius"))
			p->sp[p->sp_count - 1].rad = get_double(word3);
		else if (!ft_strcmp(*line, "specular"))
			p->sp[p->sp_count - 1].specular = get_double(word3);
		else if (!(**line == '/' && *(*line + 1) == '/'))
			STOP;
		gnl(fd, line);
	}
}

void			read_file(t_param *p, char *filename)
{
	int		fd;
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	if ((fd = open(filename, O_RDONLY)) == -1)
		STOP;
	gnl(fd, &line);
	while (line)
	{
		if (!ft_strcmp(line, "/light"))
			get_light(p, fd, &line);
		else if (!ft_strcmp(line, "/sphere"))
			get_sphere(p, fd, &line);
		else if (!ft_strcmp(line, "/cylinder"))
			get_cyl(p, fd, &line);
		else if (!ft_strcmp(line, "/cone"))
			get_cone(p, fd, &line);
		else if (!ft_strcmp(line, "/plane"))
			get_plane(p, fd, &line);
		else if (!ft_strcmp(line, "/cam"))
			get_cam(p, fd, &line);
		gnl(fd, &line);
	}
}
