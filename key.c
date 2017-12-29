/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 14:30:33 by okovalov          #+#    #+#             */
/*   Updated: 2017/08/23 12:01:14 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		exit_x(void *par)
{
	par = NULL;
	exit(1);
	return (0);
}

void	movepls(t_param *w)
{
	if (w->objform == 0)
		w->obj.spheres[0].pos.z -= 20;
	else if (w->objform == 1)
		w->obj.spheres[1].pos.z -= 20;
	else if (w->objform == 2)
		w->obj.cl.pos.z -= 20;
	else if (w->objform == 3)
		w->obj.cn.pos.z -= 20;
	else if (w->objform == 4)
		w->obj.pl[0].d -= 20;
	else if (w->objform == -1)
		w->rott.zz -= 50;
}

void	movemin(t_param *w)
{
	if (w->objform == 0)
		w->obj.spheres[0].pos.z += 20;
	else if (w->objform == 1)
		w->obj.spheres[1].pos.z += 20;
	else if (w->objform == 2)
		w->obj.cl.pos.z += 20;
	else if (w->objform == 3)
		w->obj.cn.pos.z += 20;
	else if (w->objform == 4)
		w->obj.pl[0].d += 20;
	else if (w->objform == -1)
		w->rott.zz += 50;
}

void	moveleft(t_param *w)
{
	if (w->objform == 0)
		w->obj.spheres[0].pos.x -= 20;
	else if (w->objform == 1)
		w->obj.spheres[1].pos.x -= 20;
	else if (w->objform == 2)
		w->obj.cl.pos.x -= 20;
	else if (w->objform == 3)
		w->obj.cn.pos.x -= 20;
	else if (w->objform == -1)
		w->rott.xx -= 50;
}

void	moveright(t_param *w)
{
	if (w->objform == 0)
		w->obj.spheres[0].pos.x += 20;
	else if (w->objform == 1)
		w->obj.spheres[1].pos.x += 20;
	else if (w->objform == 2)
		w->obj.cl.pos.x += 20;
	else if (w->objform == 3)
		w->obj.cn.pos.x += 20;
	else if (w->objform == -1)
		w->rott.xx += 50;
}
