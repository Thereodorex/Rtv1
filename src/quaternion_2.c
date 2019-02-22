/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 15:42:25 by jcorwin           #+#    #+#             */
/*   Updated: 2019/02/22 15:42:28 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_quat	quat_invert(t_quat q)
{
	t_quat res;

	res.w = q.w;
	res.x = -q.x;
	res.y = -q.y;
	res.z = -q.z;
	return (quat_scale(res, 1 / quat_length(res)));
}
