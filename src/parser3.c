/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 16:51:45 by jcorwin           #+#    #+#             */
/*   Updated: 2019/02/21 20:45:08 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	plane_real(t_param *p)
{
	int			i;
	t_plane		*new;

	++p->plane_count;
	new = (t_plane *)malloc(sizeof(t_plane) * p->plane_count);
	i = -1;
	while (++i < p->plane_count - 1)
		new[i] = p->plane[i];
	new[i].point = vec_new(0, 0, 5000);
	new[i].norm = vec_new(0, 0, 0);
	new[i].specular = 500;
	new[i].color = 0xffffff;
	if (p->plane)
		free(p->plane);
	p->plane = new;
}

void	l_real(t_param *p)
{
	int			i;
	t_light		*new;

	++p->l_count;
	new = (t_light *)malloc(sizeof(t_light) * p->l_count);
	i = -1;
	while (++i < p->l_count - 1)
		new[i] = p->l[i];
	new[i].pos = vec_new(0.0, 0.0, 0.0);
	new[i].intens = 0.5;
	new[i].dir = vec_new(0.0, 0.0, 1.0);
	if (p->l)
		free(p->l);
	p->l = new;
}

void	sp_real(t_param *p)
{
	int			i;
	t_sphere	*new;

	++p->sp_count;
	new = (t_sphere *)malloc(sizeof(t_sphere) * p->sp_count);
	i = -1;
	while (++i < p->sp_count - 1)
		new[i] = p->sp[i];
	new[i].rad = 1000;
	new[i].cen = vec_new(0, 0, 10000);
	new[i].specular = 500;
	new[i].color = 0xff;
	if (p->sp)
		free(p->sp);
	p->sp = new;
}

void	con_real(t_param *p)
{
	int			i;
	t_con		*new;

	++p->con_count;
	new = (t_con *)malloc(sizeof(t_con) * p->con_count);
	i = -1;
	while (++i < p->con_count - 1)
		new[i] = p->con[i];
	new[i].cen = vec_new(0, 0, 10000);
	new[i].dir = vec_new(0, 1, 0);
	new[i].cos = 0.3;
	new[i].specular = 500;
	new[i].color = 0xff;
	if (p->con)
		free(p->con);
	p->con = new;
}

void	cyl_real(t_param *p)
{
	int			i;
	t_cyl		*new;

	++p->cyl_count;
	new = (t_cyl *)malloc(sizeof(t_cyl) * p->cyl_count);
	i = -1;
	while (++i < p->cyl_count - 1)
		new[i] = p->cyl[i];
	new[i].cen = vec_new(0, 0, 10000);
	new[i].dir = vec_new(0, 1, 0);
	new[i].rad = 1000;
	new[i].specular = 500;
	new[i].color = 0xff;
	if (p->cyl)
		free(p->cyl);
	p->cyl = new;
}
