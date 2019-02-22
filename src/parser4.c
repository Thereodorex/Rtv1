/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:47:30 by jcorwin           #+#    #+#             */
/*   Updated: 2019/02/22 15:44:38 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		get_cam(t_param *p, int fd, char **line)
{
	char	*word2;
	char	*word3;

	gnl(fd, line);
	while (*line && **line && **line != ' ')
	{
		word2 = get_word(*line);
		word3 = get_word(word2);
		if (!ft_strcmp(*line, "position"))
			p->ray.cam = get_vec(word3);
		else if (!ft_strcmp(*line, "scene"))
			p->ray.scene = get_vec(word3);
		else if (!(**line == '/' && *(*line + 1) == '/'))
			STOP;
		gnl(fd, line);
	}
}

static void	get_type(t_param *p, char *type)
{
	if (!ft_strcmp(type, "ambient"))
		p->l[p->l_count - 1].type = ambient;
	else if (!ft_strcmp(type, "point"))
		p->l[p->l_count - 1].type = point;
	else if (!ft_strcmp(type, "direct"))
		p->l[p->l_count - 1].type = direct;
	else
		STOP;
}

void		get_light(t_param *p, int fd, char **line)
{
	char	*word2;
	char	*word3;

	l_real(p);
	gnl(fd, line);
	while (*line && **line && **line != ' ')
	{
		word2 = get_word(*line);
		word3 = get_word(word2);
		if (!ft_strcmp(*line, "type"))
			get_type(p, word3);
		else if (!ft_strcmp(*line, "position"))
			p->l[p->l_count - 1].pos = get_vec(word3);
		else if (!ft_strcmp(*line, "intensity"))
			p->l[p->l_count - 1].intens = get_double(word3);
		else if (!ft_strcmp(*line, "direction"))
			p->l[p->l_count - 1].dir = get_vec(word3);
		else if (!(**line == '/' && *(*line + 1) == '/'))
			STOP;
		gnl(fd, line);
	}
}
