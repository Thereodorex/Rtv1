/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:44:09 by jcorwin           #+#    #+#             */
/*   Updated: 2019/02/22 15:44:11 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

unsigned int	new_color(unsigned int color, double light_ratio)
{
	int x;
	int y;
	int z;

	x = color / 256 / 256;
	y = (color / 256) % 256;
	z = color % 256;
	x *= light_ratio;
	y *= light_ratio;
	z *= light_ratio;
	if (x > 255)
		x = 255;
	if (y > 255)
		y = 255;
	if (z > 255)
		z = 255;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (z < 0)
		z = 0;
	return (x * 256 * 256 + y * 256 + z);
}

int				is_shadow(t_param *param, t_vec p, t_vec light_ray)
{
	t_intersection2	j;
	double			t;
	t_figure		sphere;

	t = -1;
	j.t_min = 0.00001;
	j.t_max = 1;
	j.param = param;
	j.ray = light_ray;
	j.source = p;
	intersection_with_sphere(&sphere, &t, j);
	if (t != -1)
		return (0);
	intersection_with_cone(&sphere, &t, j);
	if (t != -1)
		return (0);
	intersection_with_cylinder(&sphere, &t, j);
	if (t != -1)
		return (0);
	intersection_with_plane(&sphere, &t, j);
	if (t == -1)
		return (1);
	return (0);
}

double			color_with_light2(t_param *param, t_vec ray,\
t_figure sphere, int i)
{
	t_ren_light p_l;

	p_l.intensity = 0;
	if ((param->l + i)->type == direct)
		p_l.light_ray = (param->l + i)->dir;
	if ((param->l + i)->type == point)
		p_l.light_ray = vec_frompoint((param->l + i)->pos, sphere.p);
	if (is_shadow(param, sphere.p, p_l.light_ray))
	{
		p_l.n_dot_l = vec_scal(sphere.norm_vec, p_l.light_ray);
		if (p_l.n_dot_l > 0)
			p_l.intensity += (param->l + i)->intens * p_l.n_dot_l\
					/ (vec_len(sphere.norm_vec) * vec_len(p_l.light_ray));
		if (sphere.specular != -1)
		{
			p_l.r = vec_frompoint(vec_mult(2 * p_l.n_dot_l, sphere.norm_vec),\
					p_l.light_ray);
			p_l.r_dot_v = vec_scal(p_l.r, vec_mult(-1, ray));
			if (p_l.r_dot_v > 0)
				p_l.intensity += (param->l + i)->intens * pow(p_l.r_dot_v /\
						(vec_len(p_l.r) * vec_len(vec_mult(-1, ray))),\
						sphere.specular);
		}
	}
	return (p_l.intensity);
}

unsigned int	color_with_light(t_param *param, t_vec ray, t_figure sphere)
{
	int		i;
	double	intensity;

	i = 0;
	intensity = 0;
	while (i < param->l_count)
	{
		if ((param->l + i)->type == ambient)
			intensity += (param->l + i)->intens;
		else
		{
			intensity += color_with_light2(param, ray, sphere, i);
		}
		i++;
	}
	return (new_color(sphere.color, intensity));
}
