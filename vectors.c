/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 14:35:29 by okovalov          #+#    #+#             */
/*   Updated: 2017/07/13 15:16:29 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector		vsub(t_vector *v1, t_vector *v2)
{
	t_vector	result;

	result.x = v1->x - v2->x;
	result.y = v1->y - v2->y;
	result.z = v1->z - v2->z;
	return (result);
}

double			vdot(t_vector *v1, t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vector		vscale(double c, t_vector *v)
{
	t_vector	result;

	result.x = v->x * c;
	result.y = v->y * c;
	result.z = v->z * c;
	return (result);
}

t_vector		vadd(t_vector *v1, t_vector *v2)
{
	t_vector	result;

	result.x = v1->x + v2->x;
	result.y = v1->y + v2->y;
	result.z = v1->z + v2->z;
	return (result);
}

double			vcos(t_vector *v1, t_vector *v2)
{
	double		v;
	double		n;

	v = vdot(v1, v2);
	n = sqrtf(v1->x * v1->x + v1->y * v1->y + v1->z * v1->z)
		* sqrtf(v2->x * v2->x + v2->y * v2->y + v2->z * v2->z);
	return (v / n);
}
