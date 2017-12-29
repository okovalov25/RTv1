/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 15:36:21 by okovalov          #+#    #+#             */
/*   Updated: 2017/08/24 12:57:41 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			intersectraysphere(t_ray *r, t_sphere *s, double *t)
{
	t_inter	ntr;

	ntr.retval = 0;
	ntr.a = vdot(&r->dir, &r->dir);
	ntr.dist = vsub(&r->start, &s->pos);
	ntr.b = 2 * vdot(&r->dir, &ntr.dist);
	ntr.c = vdot(&ntr.dist, &ntr.dist) - (s->radius * s->radius);
	ntr.discr = ntr.b * ntr.b - 4 * ntr.a * ntr.c;
	ntr.retval = dis(ntr, t, 0);
	return (ntr.retval);
}

int			intersectraycyl(t_ray *r, t_cyll *cl, double *t)
{
	t_inter	ntr;

	ntr.retval = 0;
	ntr.tema = vscale(vdot(&r->dir, &cl->dir), &cl->dir);
	ntr.temp = vsub(&r->dir, &ntr.tema);
	ntr.a = vdot(&ntr.temp, &ntr.temp);
	ntr.dist = vsub(&r->start, &cl->pos);
	ntr.temb2 = vscale(vdot(&ntr.dist, &cl->dir), &cl->dir);
	ntr.temb = vsub(&ntr.dist, &ntr.temb2);
	ntr.b = 2 * vdot(&ntr.temp, &ntr.temb);
	ntr.c = vdot(&ntr.temb, &ntr.temb) - (cl->radius * cl->radius);
	ntr.discr = ntr.b * ntr.b - 4 * ntr.a * ntr.c;
	ntr.retval = dis(ntr, t, 1);
	return (ntr.retval);
}

int			intersectraycon(t_ray *r, t_cone *cn, double *t)
{
	t_inter	ntr;

	ntr.retval = 0;
	ntr.tema = vscale(vdot(&r->dir, &cn->dir), &cn->dir);
	ntr.temp = vsub(&r->dir, &ntr.tema);
	ntr.tema2 = vdot(&ntr.temp, &ntr.temp);
	ntr.temp2 = vdot(&r->dir, &cn->dir);
	ntr.a = pow(cos(cn->angle), 2) * ntr.tema2 - pow(sin(cn->angle), 2)
		* ntr.temp2 * ntr.temp2;
	ntr.dist = vsub(&r->start, &cn->pos);
	ntr.temb2 = vscale(vdot(&ntr.dist, &cn->dir), &cn->dir);
	ntr.temb = vsub(&ntr.dist, &ntr.temb2);
	ntr.b = (2 * pow(cos(cn->angle), 2) * vdot(&ntr.temp, &ntr.temb))
		- (2 * pow(sin(cn->angle), 2) * vdot(&r->dir, &cn->dir)
		* vdot(&ntr.dist, &cn->dir));
	ntr.temc = vdot(&ntr.temb, &ntr.temb);
	ntr.temc2 = vdot(&ntr.dist, &cn->dir);
	ntr.c = pow(cos(cn->angle), 2) * ntr.temc - pow(sin(cn->angle), 2)
		* ntr.temc2 * ntr.temc2;
	ntr.discr = ntr.b * ntr.b - 4 * ntr.a * ntr.c;
	ntr.retval = dis(ntr, t, 1);
	return (ntr.retval);
}

int			intersectplane(t_ray *r, t_plane *pl, double *t)
{
	t_inter	ntr;

	ntr.retval = 0;
	ntr.temc = vdot(&pl->dir, &r->dir);
	ntr.temp2 = -pl->d - vdot(&pl->dir, &r->start);
	ntr.t0 = ntr.temp2 / ntr.temc;
	if ((ntr.t0 > 0.001f) && (ntr.t0 < *t))
	{
		*t = ntr.t0;
		ntr.retval = 1;
	}
	else
		ntr.retval = 0;
	return (ntr.retval);
}

int			dis(t_inter ntr, double *t, int c)
{
	double	cc;

	cc = 1;
	if (c == 1)
		cc = ntr.a;
	if (ntr.discr < 0)
		ntr.retval = 0;
	else
	{
		ntr.sqrtdiscr = sqrt(ntr.discr);
		ntr.t0 = (-ntr.b + ntr.sqrtdiscr) / (2 * cc);
		ntr.t1 = (-ntr.b - ntr.sqrtdiscr) / (2 * cc);
		if (ntr.t0 > ntr.t1)
			ntr.t0 = ntr.t1;
		if ((ntr.t0 > 0.001f) && (ntr.t0 < *t))
		{
			*t = ntr.t0;
			ntr.retval = 1;
		}
		else
			ntr.retval = 0;
	}
	return (ntr.retval);
}
