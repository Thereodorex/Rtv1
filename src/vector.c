/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:03:40 by jcorwin           #+#    #+#             */
/*   Updated: 2019/02/22 15:43:21 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec		vec_frompoint(t_vec p1, t_vec p2)
{
	t_vec	res;

	res.x = p1.x - p2.x;
	res.y = p1.y - p2.y;
	res.z = p1.z - p2.z;
	return (res);
}

t_vec		vec_new(double x, double y, double z)
{
	t_vec new_vec;

	new_vec.x = x;
	new_vec.y = y;
	new_vec.z = z;
	return (new_vec);
}

t_vec		vec_sum(t_vec v1, t_vec v2)
{
	t_vec	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_vec		vec_mult(double a, t_vec res)
{
	res.x *= a;
	res.y *= a;
	res.z *= a;
	return (res);
}
