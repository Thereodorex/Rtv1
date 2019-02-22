/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:42:07 by jcorwin           #+#    #+#             */
/*   Updated: 2019/02/22 15:42:10 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_quat	create_quat(t_vec rotate_vector, double rotate_angle)
{
	t_quat quat;

	rotate_vector = vec_mult(1 / vec_len(rotate_vector), rotate_vector);
	quat.w = cos(rotate_angle / 2);
	quat.x = rotate_vector.x * sin(rotate_angle / 2);
	quat.y = rotate_vector.y * sin(rotate_angle / 2);
	quat.z = rotate_vector.z * sin(rotate_angle / 2);
	return (quat);
}

t_quat	quat_mul_quat(t_quat a, t_quat b)
{
	t_quat res;

	res.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
	res.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
	res.y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
	res.z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;
	return (res);
}

t_quat	quat_mul_vector(t_quat a, t_vec b)
{
	t_quat res;

	res.w = -a.x * b.x - a.y * b.y - a.z * b.z;
	res.x = a.w * b.x + a.y * b.z - a.z * b.y;
	res.y = a.w * b.y - a.x * b.z + a.z * b.x;
	res.z = a.w * b.z + a.x * b.y - a.y * b.x;
	return (res);
}

double	quat_length(t_quat q)
{
	return (sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z));
}

t_quat	quat_scale(t_quat q, double val)
{
	q.w = q.w * val;
	q.x = q.x * val;
	q.y = q.y * val;
	q.z = q.z * val;
	return (q);
}
