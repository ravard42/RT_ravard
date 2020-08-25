#include "rt.h"

#define COND_0 (e->c.ori[2] > 2 * e->o->onde[0] && e->c.ray[2] < 0)
#define DK			0.1
#define TOL			0.1
#define ITER_MAX	1000

/*
** cf ondePlane_inter.c
**
**	(E)
**	soit (u,v) dans R
**	x=u \ xlim[0]<u<xlim[1]
**	y=v \ ylim[0]<v<ylim[1]
**	z=a*cos(ω*u + φ) + a*cos(ω*v + φ)
**
**	en mettant M dans (E) on obtient donc cz + k*rz = a*cos(ω*(cx + k*rx) + φ) + a*cos(ω*(cy + k*ry) + φ)
**	on pose maintenant g(k) = cz + k*rz -a * (cos(ω*(cx + k*rx) + φ) + cos(ω*(cy + k*ry) + φ))
*/


static float		g(float k, float *param)
{
	float 	cosx;
	float 	cosy;

	cosx = cos(param[1] * (param[3] + k * param[6]) + param[2]);
	cosy = cos(param[1] * (param[4] + k * param[7]) + param[2]);

	return (param[5] + k * param[8] - param[0] * (cosx + cosy));
}

/*
** 	param:
**	0 : a
**	1 : ω
**	2 : φ
**	3 : cx
**	4 : cy
**	5 : cz
**	6 : rx
**	7 : ry
**	8 : rz
*/

void				biOndePlane_inter(t_env *e)
{
	float	i;
	float	k;
	float	param[9];
	float	inter_x;
	float	inter_y;

	if (COND_0)
	{
		i = -1;
		k = (2 * e->o->onde[0] - e->c.ori[2]) / e->c.ray[2] - 0.01;
		param[0] = e->o->onde[0];
		param[1] = 2 * M_PI * e->o->onde[1];
		param[2] = e->o->onde[2];
		param[3] = e->c.ori[0];
		param[4] = e->c.ori[1];
		param[5] = e->c.ori[2];
		param[6] = e->c.ray[0];
		param[7] = e->c.ray[1];
		param[8] = e->c.ray[2];
		while (fabs(g(k, param)) > TOL && ++i < ITER_MAX)
			k += DK;
		inter_x = e->c.ori[0] + k * e->c.ray[0];
		inter_y = e->c.ori[1] + k * e->c.ray[1];
		if (k <= e->c.inter
			&& inter_x >= e->o->xlim[0] && inter_x <= e->o->xlim[1]
			&& inter_y >= e->o->ylim[0] && inter_y <= e->o->ylim[1])
		{
			e->c.inter = k;
			e->c.obj = e->o;
		}
	}
}
