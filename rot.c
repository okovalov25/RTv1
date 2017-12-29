/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 13:16:05 by okovalov          #+#    #+#             */
/*   Updated: 2017/08/24 13:14:33 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		rtkey(int keycode, t_param *w)
{
	if (keycode == 0 && w->rott.angly > -35)
		w->rott.angly -= 5;
	else if (keycode == 2 && w->rott.angly < 35)
		w->rott.angly += 5;
	else if (keycode == 13 && w->rott.anglx < 35)
		w->rott.anglx += 5;
	else if (keycode == 1 && w->rott.anglx > -35)
		w->rott.anglx -= 5;
	else if (keycode == 12 && w->rott.anglz < 180)
		w->rott.anglz += 5;
	else if (keycode == 14 && w->rott.anglz > -180)
		w->rott.anglz -= 5;
	calcangl(w);
	rottn(w, 0);
}

void		rottn(t_param *w, int v)
{
	double	sm1;
	double	sm2;
	double	sm3;
	double	sm4;

	sm1 = w->rott.sny * w->rott.snx - w->rott.csy * w->rott.snz * w->rott.csx;
	sm2 = w->rott.csy * w->rott.snz * w->rott.snx + w->rott.sny * w->rott.csx;
	sm3 = w->rott.sny * w->rott.snz * w->rott.csx + w->rott.snx * w->rott.csy;
	sm4 = w->rott.csy * w->rott.csx - w->rott.snx * w->rott.sny * w->rott.snz;
	if (v == 1)
	{
		w->rt.x = w->x * w->rott.csy * w->rott.csz + w->y * sm1 + w->z * sm2;
		w->rt.y = w->x * w->rott.snz + w->y * w->rott.csz * w->rott.csx + w->z
			* w->rott.csz * w->rott.snx;
		w->rt.z = w->x * w->rott.sny * w->rott.csz + w->y * sm3 + w->z * sm4;
	}
	else
	{
		w->r.startr.x = w->r.start.x * w->rott.csy * w->rott.csz
			+ w->r.start.y * sm1 + w->r.start.z * sm2;
		w->r.startr.y = w->r.start.x * w->rott.snz + w->r.start.y * w->rott.csz
			* w->rott.csx + w->r.start.z * w->rott.csz * w->rott.snx;
		w->r.startr.z = w->r.start.x * w->rott.sny * w->rott.csz
			+ w->r.start.y * sm3 + w->r.start.z * sm4;
	}
}

void		calcangl(t_param *w)
{
	w->r.start.x = 0 + w->rott.xx;
	w->r.start.y = 0 + w->rott.yy;
	w->r.start.z = -2000 + w->rott.zz;
	w->rott.snx = sin(w->rott.anglx * RAD);
	w->rott.sny = sin(w->rott.angly * RAD);
	w->rott.snz = sin(w->rott.anglz * RAD);
	w->rott.csx = cos(w->rott.anglx * RAD);
	w->rott.csy = cos(w->rott.angly * RAD);
	w->rott.csz = cos(w->rott.anglz * RAD);
}

void		pln(t_param *w)
{
	w->obj.pl[0].d = 300;
	w->obj.pl[0].dir.x = 0;
	w->obj.pl[0].dir.y = 0;
	w->obj.pl[0].dir.z = -1;
	w->obj.pl[0].material = 3;
	w->obj.pl[1].d = 300;
	w->obj.pl[1].dir.x = 0;
	w->obj.pl[1].dir.y = -1;
	w->obj.pl[1].dir.z = 0;
	w->obj.pl[1].material = 3;
	w->obj.pl[2].d = 400;
	w->obj.pl[2].dir.x = 1;
	w->obj.pl[2].dir.y = 0;
	w->obj.pl[2].dir.z = 0;
	w->obj.pl[2].material = 3;
	w->obj.pl[3].d = 400;
	w->obj.pl[3].dir.x = -1;
	w->obj.pl[3].dir.y = 0;
	w->obj.pl[3].dir.z = 0;
	w->obj.pl[3].material = 3;
	w->obj.pl[4].d = 300;
	w->obj.pl[4].dir.x = 0;
	w->obj.pl[4].dir.y = 1;
	w->obj.pl[4].dir.z = 0;
	w->obj.pl[4].material = 3;
}

void		cam(t_param *w)
{
	w->r.start.x = 0;
	w->r.start.y = 0;
	w->r.start.z = -2000;
	w->rott.xx = 0;
	w->rott.yy = 0;
	w->rott.zz = 0;
	w->r.startr = w->r.start;
	w->rott.anglx = 0;
	w->rott.angly = 0;
	w->rott.anglz = 0;
	w->objform = -1;
	w->z = 0;
}
