/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:46:29 by jcorwin           #+#    #+#             */
/*   Updated: 2019/02/22 20:21:33 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

t_vec			rot(double angle, t_vec u, t_vec v)
{
	t_quat quat;
	t_quat t;

	quat = create_quat(u, angle);
	t = quat_mul_vector(quat, v);
	t = quat_mul_quat(t, quat_invert(quat));
	return (vec_new(t.x, t.y, t.z));
}

void			intersection_with_plane(t_figure *sphere,\
									double *t, t_intersection2 j, int i)
{
	double	t1;

	while (i < j.param->plane_count)
	{
		if (vec_scal(j.ray, (j.param->plane + i)->norm) /
				vec_len(j.ray) / vec_len((j.param->plane + i)->norm) > 0)
			(j.param->plane + i)->norm =
				vec_mult(-1, (j.param->plane + i)->norm);
		t1 = vec_scal(j.source, (j.param->plane + i)->norm);
		t1 += -vec_scal((j.param->plane + i)->point,\
		(j.param->plane + i)->norm);
		t1 /= -vec_scal(j.ray, (j.param->plane + i)->norm);
		if ((*t == -1 || *t > t1) && t1 > j.t_min &&\
		(j.t_max == -1 || t1 < j.t_max))
		{
			*t = t1;
			sphere->p = vec_sum(j.source, vec_mult(*t, j.ray));
			sphere->norm_vec = (j.param->plane + i)->norm;
			sphere->norm_vec = vec_mult(1 /\
			vec_len(sphere->norm_vec), sphere->norm_vec);
			sphere->color = (j.param->plane + i)->color;
			sphere->specular = (j.param->plane + i)->specular;
		}
		i++;
	}
}

void			intersection(t_figure *sphere, double *t,\
t_param *param, t_vec ray)
{
	t_intersection2 j;

	*t = -1;
	j.t_max = -1;
	j.t_min = 1;
	j.source = param->ray.cam;
	j.param = param;
	j.ray = ray;
	intersection_with_sphere(sphere, t, j);
	intersection_with_cone(sphere, t, j);
	intersection_with_cylinder(sphere, t, j);
	intersection_with_plane(sphere, t, j, 0);
}

static t_vec	init_ray(double angle_1, double angle_2,
								t_param *param, t_vec ray)
{
	if (angle_1 != 0 && angle_1 == angle_1)
		ray = rot(-angle_1, param->ray.ray, ray);
	if (angle_2 != 0 && angle_2 == angle_2)
		ray = rot(angle_2, param->ray.ray2, ray);
	return (ray);
}

int				render(t_sdl *sdl, t_param *param,
							double angle1, double angle2)
{
	int			x;
	int			y;
	t_vec		ray;
	t_figure	sphere;
	double		t;

	x = -sdl->surf->w / 2;
	while (x < sdl->surf->w / 2)
	{
		y = -sdl->surf->h / 2;
		while (y < sdl->surf->h / 2)
		{
			ray = vec_new(x, y, 1000);
			ray = init_ray(angle1, angle2, param, ray);
			intersection(&sphere, &t, param, ray);
			if (t != -1)
				sdl_putpix(sdl, x + sdl->surf->w / 2, y + sdl->surf->h / 2, \
				color_with_light(param, ray, sphere));
			else
				sdl_putpix(sdl, x + sdl->surf->w / 2, y + sdl->surf->h / 2, 0);
			y++;
		}
		x++;
	}
	return (0);
}
