/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 15:50:52 by okovalov          #+#    #+#             */
/*   Updated: 2017/08/24 12:54:57 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			key2(int keycode, t_param *w)
{
	if (keycode == 15)
	{
		if (w->obj.cn.dir.x == 1 && w->obj.cn.dir.y++ == 0)
			w->obj.cn.dir.x = 0;
		else if (w->obj.cn.dir.y == 1 && w->obj.cn.dir.x++ == 0)
			w->obj.cn.dir.y = 0;
	}
	else if (keycode == 17)
	{
		if (w->obj.cl.dir.x == 1 && w->obj.cl.dir.y++ == 0)
			w->obj.cl.dir.x = 0;
		else if (w->obj.cl.dir.y == 1 && w->obj.cl.dir.x++ == 0)
			w->obj.cl.dir.y = 0;
	}
	else if (keycode == 125)
		moveup(w);
	else if (keycode == 126)
		movedouwn(w);
	else if (keycode == 69)
		movepls(w);
	else if (keycode == 78)
		movemin(w);
	else if (keycode == 124)
		moveright(w);
}

int				key(int keycode, t_param *w)
{
	if (keycode == 53)
		exit(1);
	else if (keycode > 17 && keycode < 23)
		w->objform = keycode - 18;
	else if (keycode == 123)
		moveleft(w);
	else if (keycode == 8)
		w->objform = -1;
	else if (keycode >= 0 && keycode <= 14)
		rtkey(keycode, w);
	else
		key2(keycode, w);
	if (keycode == 24 && w->lights[0].intensity < 1.5)
	{
		w->lights[0].intensity += 0.1;
		w->lights[1].intensity += 0.1;
	}
	else if (keycode == 27 && w->lights[1].intensity > 0.1)
	{
		w->lights[0].intensity -= 0.1;
		w->lights[1].intensity -= 0.1;
	}
	mlx_destroy_image(w->mlx, w->img);
	calc(*w);
	return (1);
}

int				main(void)
{
	t_param		w;

	par(&w);
	w.mlx = mlx_init();
	w.win = mlx_new_window(w.mlx, WIDTH, HEIGHT, "RTv1");
	calc(w);
	return (1);
}

void			calc(t_param w)
{
	w.img = mlx_new_image(w.mlx, WIDTH, HEIGHT);
	w.line = mlx_get_data_addr(w.img, &w.bpp, &w.sl, &w.nd);
	calcangl(&w);
	w.y = -HEIGHT / 2;
	while (w.y++ < HEIGHT / 2)
	{
		w.x = -WIDTH / 2;
		while (w.x++ < WIDTH / 2)
		{
			rottn(&w, 1);
			w.r.dir.x = w.rt.x - w.r.startr.x;
			w.r.dir.y = w.rt.y - w.r.startr.y;
			w.r.dir.z = w.rt.z - w.r.startr.z;
			w.r.dir = nvector(&w.r.dir);
			w.t = 20000;
			w.currentobj = -1;
			w.currentobj = interobj(w.r, w.obj, &w.t);
			normal1(&w);
			lght(w);
		}
	}
	mlx_put_image_to_window(w.mlx, w.win, w.img, 0, 0);
	mlx_hook(w.win, 2, 5, key, &w);
	mlx_hook(w.win, 17, 1L << 17, exit_x, &w);
	mlx_loop(w.mlx);
}

void			lght(t_param w)
{
	double		t;
	int			j;
	t_vector	dist;
	int			pixel;

	w.red = 0;
	w.green = 0;
	w.blue = 0;
	j = -1;
	while (++j < 2)
	{
		w.currentlight = w.lights[j];
		dist = vsub(&w.currentlight.pos, &w.newstart);
		if (vdot(&w.n, &dist) <= 0.0f)
			continue;
		t = sqrtf(vdot(&dist, &dist));
		if (t <= 0.0f)
			continue;
		lt(&w, t, dist);
	}
	pixel = (int)(((w.x + WIDTH / 2) + (w.y + HEIGHT / 2) * WIDTH) * 4);
	w.line[pixel] = (unsigned char)MIN(w.blue * 255, 255);
	w.line[pixel + 1] = (unsigned char)MIN(w.green * 255, 255);
	w.line[pixel + 2] = (unsigned char)MIN(w.red * 255, 255);
}
