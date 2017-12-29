/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matnlig.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 15:27:03 by okovalov          #+#    #+#             */
/*   Updated: 2017/08/28 14:32:33 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		par(t_param *w)
{
	w->obj.spheres[0].pos.x = -100;
	w->obj.spheres[0].pos.y = -100;
	w->obj.spheres[0].pos.z = -100;
	w->obj.spheres[0].radius = 70;
	w->obj.spheres[0].material = 0;
	w->obj.spheres[1].pos.x = 100;
	w->obj.spheres[1].pos.y = -100;
	w->obj.spheres[1].pos.z = -100;
	w->obj.spheres[1].radius = 70;
	w->obj.spheres[1].material = 0;
	w->obj.cl.pos.x = -50;
	w->obj.cl.pos.y = 50;
	w->obj.cl.pos.z = 50;
	w->obj.cl.radius = 50;
	w->obj.cl.dir.x = 1;
	w->obj.cl.dir.y = 0;
	w->obj.cl.dir.z = 0;
	w->obj.cl.material = 1;
	w->obj.cn.pos.y = -10;
	w->obj.cn.pos.z = -100;
	w->obj.cn.angle = 10 * RAD;
	w->obj.cn.dir.x = 0;
	w->obj.cn.dir.y = 1;
	w->obj.cn.dir.z = 0;
	mat(w);
}

void		mat(t_param *w)
{
	w->objform = -1;
	w->materials[0].diffuse.red = 1;
	w->materials[0].diffuse.green = 0;
	w->materials[0].diffuse.blue = 0;
	w->materials[1].diffuse.red = 0;
	w->materials[1].diffuse.green = 1;
	w->materials[1].diffuse.blue = 0;
	w->materials[2].diffuse.red = 0;
	w->materials[2].diffuse.green = 0;
	w->materials[2].diffuse.blue = 1;
	w->materials[3].diffuse.red = 0.6;
	w->materials[3].diffuse.green = 0;
	w->materials[3].diffuse.blue = 0.8;
	w->lights[0].pos.x = 300;
	w->lights[0].pos.y = -200;
	w->lights[0].pos.z = -300;
	w->lights[0].intensity = 0.7;
	w->lights[1].pos.x = -100;
	w->lights[1].pos.y = 50;
	w->lights[1].pos.z = -300;
	w->lights[1].intensity = 0.4;
	w->obj.cn.material = 2;
	pln(w);
	cam(w);
}

void		moveup(t_param *w)
{
	if (w->objform == 0)
		w->obj.spheres[0].pos.y += 20;
	else if (w->objform == 1)
		w->obj.spheres[1].pos.y += 20;
	else if (w->objform == 2)
		w->obj.cl.pos.y += 20;
	else if (w->objform == 3)
		w->obj.cn.pos.y += 20;
	else if (w->objform == -1)
		w->rott.yy += 50;
}

void		movedouwn(t_param *w)
{
	if (w->objform == 0)
		w->obj.spheres[0].pos.y -= 20;
	else if (w->objform == 1)
		w->obj.spheres[1].pos.y -= 20;
	else if (w->objform == 2)
		w->obj.cl.pos.y -= 20;
	else if (w->objform == 3)
		w->obj.cn.pos.y -= 20;
	else if (w->objform == -1)
		w->rott.yy -= 50;
}

void		lt(t_param *w, double t, t_vector dist)
{
	double	lambert;
	double	cs;
	double	blinn;

	w->lightray.start = w->newstart;
	w->lightray.dir = vscale((1 / t), &dist);
	if (interobj(w->lightray, w->obj, &t) == -1)
	{
		cs = vcos(&w->n, &w->lightray.dir);
		blinn = pow(cs, 30);
		lambert = vdot(&w->lightray.dir, &w->n) + blinn;
		w->red += lambert * w->currentlight.intensity
			* w->currentmat.diffuse.red;
		w->green += lambert * w->currentlight.intensity
			* w->currentmat.diffuse.green;
		w->blue += lambert * w->currentlight.intensity
			* w->currentmat.diffuse.blue;
	}
}
