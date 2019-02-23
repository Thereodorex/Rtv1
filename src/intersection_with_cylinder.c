/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_with_cylinder.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:45:00 by jcorwin           #+#    #+#             */
/*   Updated: 2019/02/23 17:29:03 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

void		intersection_with_cylinder2(t_figure *sphere, double *t,\
t_intersection2 j, t_intersection i)
{
	i.t2 = (-i.k.k2 + sqrt(i.dis)) / (2 * i.k.k1);
	i.t1 = (-i.k.k2 - sqrt(i.dis)) / (2 * i.k.k1);
	if (i.t1 > i.t2 && (j.t_max != -1 || i.t2 >= 1))
		i.t1 = i.t2;
	if ((*t == -1 || *t > i.t1) && i.t1 > j.t_min &&\
	(j.t_max == -1 || i.t1 < j.t_max))
	{
		*t = i.t1;
		sphere->p = vec_sum(j.source, vec_mult(*t, j.ray));
		i.p = sqrt((pow(vec_len(vec_frompoint(sphere->p, (j.param->cyl\
		+ i.i)->cen)), 2) - pow((j.param->cyl + i.i)->rad, 2))) /\
		vec_scal((j.param->cyl + i.i)->dir, (j.param->cyl + i.i)->dir);
		if (vec_scal((j.param->cyl + i.i)->dir, vec_frompoint(sphere->p,\
		(j.param->cyl + i.i)->cen)) / vec_len(vec_frompoint(sphere->p,\
		(j.param->cyl + i.i)->cen)) < 0)
			i.p *= -1;
		sphere->norm_vec = vec_sum(vec_mult(i.p, (j.param->cyl\
		+ i.i)->dir), vec_frompoint((j.param->cyl + i.i)->cen, sphere->p));
		sphere->norm_vec = vec_mult(-1 /\
		vec_len(sphere->norm_vec), sphere->norm_vec);
		sphere->color = (j.param->cyl + i.i)->color;
		sphere->specular = (j.param->cyl + i.i)->specular;
	}
}

void		intersection_with_cylinder(t_figure *sphere,\
double *t, t_intersection2 j)
{
	t_intersection i;

	i.i = 0;
	while (i.i < j.param->cyl_count)
	{
		(j.param->cyl + i.i)->dir = vec_mult(1 / vec_len(\
		(j.param->cyl + i.i)->dir), (j.param->cyl + i.i)->dir);
		i.oc = vec_frompoint(j.source, (j.param->cyl + i.i)->cen);
		i.k.k1 = vec_scal(j.ray, j.ray) - pow(vec_scal(j.ray,\
		(j.param->cyl + i.i)->dir), 2);
		i.k.k2 = 2 * (vec_scal(j.ray, i.oc) - vec_scal(j.ray,\
		(j.param->cyl + i.i)->dir) * vec_scal(i.oc, (j.param->cyl + i.i)->dir));
		i.k.k3 = vec_scal(i.oc, i.oc) - pow(vec_scal(i.oc,\
		(j.param->cyl + i.i)->dir), 2) - pow((j.param->cyl + i.i)->rad, 2);
		i.dis = i.k.k2 * i.k.k2 - 4 * i.k.k1 * i.k.k3;
		if (i.dis >= 0)
		{
			intersection_with_cylinder2(sphere, t, j, i);
		}
		i.i++;
	}
}
