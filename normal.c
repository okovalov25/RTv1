/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 15:46:17 by okovalov          #+#    #+#             */
/*   Updated: 2017/08/23 16:44:00 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector		nvector(t_vector *v1)
{
	double		leng;
	double		inv_length;
	t_vector	result;

	leng = sqrt((v1->x * v1->x) + (v1->y * v1->y) + (v1->z * v1->z));
	inv_length = (1 / leng);
	result.x = v1->x * inv_length;
	result.y = v1->y * inv_length;
	result.z = v1->z * inv_length;
	return (result);
}

t_vector		vcross(t_vector *v1, t_vector *v2)
{
	t_vector	result;

	result.x = (v1->y * v2->z) - (v1->z * v2->y);
	result.y = (v1->z * v2->x) - (v1->x * v2->z);
	result.z = (v1->x * v2->y) - (v1->y * v2->x);
	return (result);
}

void			normal1(t_param *w)
{
	t_vector	scaled;

	scaled = vscale(w->t, &w->r.dir);
	w->newstart = vadd(&w->r.start, &scaled);
	if (w->currentobj == 0 || w->currentobj == 1)
	{
		w->n = vsub(&w->newstart, &w->obj.spheres[w->currentobj].pos);
		w->n = nvector(&w->n);
		w->currentmat = w->materials[w->obj.spheres[0].material];
	}
	else if (w->currentobj >= 4)
	{
		w->n = w->obj.pl[w->currentobj - 4].dir;
		w->currentmat = w->materials[w->obj.pl[w->currentobj - 4].material];
	}
	else
		normal2(w, scaled);
}

void			normal2(t_param *w, t_vector scaled)
{
	t_vector	aa;
	t_vector	bb;

	if (w->currentobj == 2)
	{
		bb = vsub(&w->newstart, &w->obj.cl.pos);
		aa = vscale(vdot(&bb, &w->obj.cl.dir), &w->obj.cl.dir);
		w->n = vsub(&bb, &aa);
		w->n = nvector(&w->n);
		w->currentmat = w->materials[w->obj.cl.material];
	}
	else if (w->currentobj == 3)
	{
		bb = vsub(&w->newstart, &w->obj.cn.pos);
		aa = vscale(vcos(&bb, &w->obj.cn.dir), &w->obj.cn.dir);
		w->n = vsub(&bb, &aa);
		scaled = vcross(&bb, &w->n);
		w->n = vcross(&scaled, &bb);
		w->n = nvector(&w->n);
		w->currentmat = w->materials[w->obj.cn.material];
	}
}

int				interobj(t_ray r, t_objct obj, double *t)
{
	int			currentobj;
	int			s;

	s = -1;
	currentobj = -1;
	while (++s < 2)
		if (intersectraysphere(&r, &obj.spheres[s], t))
			currentobj = s;
	if (intersectraycyl(&r, &obj.cl, t))
		currentobj = 2;
	if (intersectraycon(&r, &obj.cn, t))
		currentobj = 3;
	s = -1;
	while (++s < 5)
		if (intersectplane(&r, &obj.pl[s], t))
			currentobj = s + 4;
	return (currentobj);
}
