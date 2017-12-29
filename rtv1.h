/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okovalov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 13:22:55 by okovalov          #+#    #+#             */
/*   Updated: 2017/08/28 14:14:42 by okovalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <mlx.h>
# include <stdlib.h>
# include <math.h>

# define MIN(a,b) (((a) < (b)) ? (a) : (b))

# define WIDTH  800
# define HEIGHT 600
# define RAD M_PI / 180

typedef struct	s_v
{
	double		x;
	double		y;
	double		z;
}				t_vector;

typedef struct	s_in
{
	int			retval;
	t_vector	tema;
	double		tema2;
	t_vector	temp;
	double		temp2;
	t_vector	temb;
	t_vector	temb2;
	double		temc;
	double		temc2;
	double		a;
	double		b;
	double		c;
	double		discr;
	t_vector	dist;
	double		t0;
	double		t1;
	double		sqrtdiscr;
}				t_inter;

typedef struct	s_sp
{
	t_vector	pos;
	double		radius;
	int			material;
}				t_sphere;

typedef struct	s_cl
{
	t_vector	pos;
	double		radius;
	t_vector	dir;
	int			material;
}				t_cyll;

typedef struct	s_cn
{
	t_vector	pos;
	double		angle;
	t_vector	dir;
	int			material;
}				t_cone;

typedef struct	s_pln
{
	double		d;
	t_vector	dir;
	int			material;
}				t_plane;

typedef struct	s_ry
{
	t_vector	start;
	t_vector	dir;
	t_vector	startr;
}				t_ray;

typedef struct	s_obj
{
	t_cyll		cl;
	t_sphere	spheres[2];
	t_cone		cn;
	t_plane		pl[5];
}				t_objct;

typedef struct	s_clr
{
	double	red;
	double	green;
	double	blue;
}				t_colour;

typedef struct	s_mat
{
	t_colour	diffuse;
}				t_mat;

typedef struct	s_lt
{
	t_vector	pos;
	double		intensity;
}				t_light;

typedef struct	s_rt
{
	double		snx;
	double		csx;
	double		sny;
	double		csy;
	double		snz;
	double		csz;
	double		anglx;
	double		angly;
	double		anglz;
	double		xx;
	double		yy;
	double		zz;
}				t_rt;

typedef struct	s_parm
{
	void		*mlx;
	void		*win;
	void		*img;
	int			bpp;
	int			sl;
	int			nd;
	char		*line;
	t_objct		obj;
	t_ray		r;
	t_mat		materials[4];
	t_light		lights[2];
	int			x;
	int			y;
	int			z;
	double		t;
	int			currentobj;
	t_vector	newstart;
	t_vector	n;
	t_vector	rt;
	t_mat		currentmat;
	int			objform;
	t_rt		rott;
	t_ray		lightray;
	t_light		currentlight;
	double		red;
	double		green;
	double		blue;
}				t_param;

void			calc(t_param w);
void			lght(t_param w);
void			normal1(t_param *w);
void			normal2(t_param *w, t_vector scaled);
void			moveleft(t_param *w);
void			moveright(t_param *w);
void			moveup(t_param *w);
void			movedouwn(t_param *w);
void			movemin(t_param *w);
void			movepls(t_param *w);
int				dis(t_inter ntr, double *t, int c);
t_vector		vsub(t_vector *v1, t_vector *v2);
double			vdot(t_vector *v1, t_vector *v2);
t_vector		vscale(double c, t_vector *v);
t_vector		vadd(t_vector *v1, t_vector *v2);
double			vcos(t_vector *v1, t_vector *v2);
int				exit_x(void *par);
void			rottn(t_param *w, int v);
void			rtkey(int keycode, t_param *w);
void			key2(int keycode, t_param *w);
void			mat(t_param *w);
int				intersectraysphere(t_ray *r, t_sphere *s, double *t);
int				intersectraycyl(t_ray *r, t_cyll *cl, double *t);
int				intersectraycon(t_ray *r, t_cone *cn, double *t);
int				intersectplane(t_ray *r, t_plane *pl, double *t);
t_vector		nvector (t_vector *v1);
t_vector		vcross(t_vector *v1, t_vector *v2);
int				interobj(t_ray r, t_objct obj, double *t);
void			par(t_param *w);
void			lt(t_param *w, double t, t_vector dist);
void			calcangl(t_param *w);
void			pln(t_param *w);
void			cam(t_param *w);

#endif
