/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_with_cone.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:44:52 by jcorwin           #+#    #+#             */
/*   Updated: 2019/02/22 15:44:54 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

void		intersection_with_cone2(t_figure *sphere, double *t,\
t_intersection2 j, t_intersection i)
{
	i.t2 = (-i.k.k2 + sqrt(i.dis)) / (2 * i.k.k1);
	i.t1 = (-i.k.k2 - sqrt(i.dis)) / (2 * i.k.k1);
	if (i.t1 > i.t2)
		i.t1 = i.t2;
	if ((*t == -1 || *t > i.t1) && i.t1 > j.t_min &&\
	(j.t_max == -1 || i.t1 < j.t_max))
	{
		*t = i.t1;
		sphere->p = vec_sum(j.source, vec_mult(*t, j.ray));
		i.p = vec_len(vec_frompoint(sphere->p, (j.param->con + i.i)->cen))\
		/ cos((j.param->con + i.i)->cos) / vec_len((j.param->con + i.i)->dir);
		if (vec_scal((j.param->con + i.i)->dir, vec_frompoint(sphere->p,\
		(j.param->con + i.i)->cen)) / (vec_len((j.param->con + i.i)->dir)\
		* vec_len(vec_frompoint(sphere->p, (j.param->con + i.i)->cen))) > 0)
			i.p *= -1;
		sphere->norm_vec = vec_sum(vec_mult(i.p, (j.param->con + i.i)->dir),\
		vec_frompoint(sphere->p, (j.param->con + i.i)->cen));
		sphere->norm_vec = vec_mult(1 / vec_len(sphere->norm_vec),\
		sphere->norm_vec);
		sphere->color = (j.param->con + i.i)->color;
		sphere->specular = (j.param->con + i.i)->specular;
	}
}

void		intersection_with_cone(t_figure *sphere,\
double *t, t_intersection2 j)
{
	t_intersection i;

	i.i = 0;
	while (i.i < j.param->con_count)
	{
		(j.param->con + i.i)->dir = vec_mult(1 / vec_len((j.param->con\
		+ i.i)->dir), (j.param->con + i.i)->dir);
		i.oc = vec_frompoint(j.source, (j.param->con + i.i)->cen);
		i.k.k1 = vec_scal(j.ray, j.ray) - (1 + pow(tan((j.param->con\
		+ i.i)->cos), 2)) * pow(vec_scal(j.ray, (j.param->con + i.i)->dir), 2);
		i.k.k2 = 2 * (vec_scal(j.ray, i.oc) - (1 + pow(tan((j.param->con\
		+ i.i)->cos), 2)) * vec_scal(j.ray, (j.param->con + i.i)->dir) *\
		vec_scal(i.oc, (j.param->con + i.i)->dir));
		i.k.k3 = vec_scal(i.oc, i.oc) - (1 + pow(tan((j.param->con\
		+ i.i)->cos), 2)) * pow(vec_scal(i.oc, (j.param->con + i.i)->dir), 2);
		i.dis = i.k.k2 * i.k.k2 - 4 * i.k.k1 * i.k.k3;
		if (i.dis >= 0)
		{
			intersection_with_cone2(sphere, t, j, i);
		}
		i.i++;
	}
}
