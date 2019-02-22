/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:43:10 by jcorwin           #+#    #+#             */
/*   Updated: 2019/02/22 15:43:44 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double			vec_scal(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec			vec_cross(t_vec v1, t_vec v2)
{
	return (vec_new(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x *
									v2.z, v1.x * v2.y - v1.y * v2.x));
}

double			vec_len(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
