/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_with_sphere.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:45:08 by jcorwin           #+#    #+#             */
/*   Updated: 2019/02/22 15:45:09 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

void		intersection_with_sphere2(t_figure *sphere, double *t,\
t_intersection2 j, t_intersection i)
{
	i.t1 = (-i.k.k2 + sqrt(i.dis)) / (2 * i.k.k1);
	i.t2 = (-i.k.k2 - sqrt(i.dis)) / (2 * i.k.k1);
	if (i.t1 > i.t2)
	{
		i.t1 = i.t2;
	}
	if ((*t == -1 || *t > i.t1) && i.t1 > j.t_min &&\
	(j.t_max == -1 || i.t1 < j.t_max))
	{
		*t = i.t1;
		sphere->p = vec_sum(j.source, vec_mult(*t, j.ray));
		sphere->norm_vec = vec_frompoint(sphere->p, (j.param->sp + i.i)->cen);
		sphere->norm_vec = vec_mult(1 / vec_len(sphere->norm_vec),\
		sphere->norm_vec);
		sphere->color = (j.param->sp + i.i)->color;
		sphere->specular = (j.param->sp + i.i)->specular;
	}
}

void		intersection_with_sphere(t_figure *sphere,\
double *t, t_intersection2 j)
{
	t_intersection i;

	i.i = 0;
	while (i.i < j.param->sp_count)
	{
		i.oc = vec_frompoint(j.source, (j.param->sp + i.i)->cen);
		i.k.k1 = vec_scal(j.ray, j.ray);
		i.k.k2 = 2 * vec_scal(i.oc, j.ray);
		i.k.k3 = vec_scal(i.oc, i.oc) - (j.param->sp + i.i)->rad\
		* (j.param->sp + i.i)->rad;
		i.dis = i.k.k2 * i.k.k2 - 4 * i.k.k1 * i.k.k3;
		if (i.dis >= 0)
		{
			intersection_with_sphere2(sphere, t, j, i);
		}
		i.i++;
	}
}
