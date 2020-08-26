#include "rt.h"

static float	solve(t_env *e)
{
	float	tmp;

	tmp = (e->o->axe[0] * (e->o->ori[0] - e->c.ori[0])
	+ e->o->axe[1] * (e->o->ori[1] - e->c.ori[1])
	+ e->o->axe[2] * (e->o->ori[2] - e->c.ori[2]))
	/ (e->o->axe[0] * e->c.ray[0]
	+ e->o->axe[1] * e->c.ray[1]
	+ e->o->axe[2] * e->c.ray[2]);
	return (tmp);
}

void				plan_inter(t_env *e)
{
	float	k;
	float	inter_x;
	float	inter_y;

	if (dot_prod(e->o->axe, e->c.ray))
	{
		k = solve(e);
		inter_x = e->c.ori[0] + k * e->c.ray[0];
		inter_y = e->c.ori[1] + k * e->c.ray[1];
		if (k >= 0 && k <= e->c.inter
			&& inter_x >= e->o->xlim[0] && inter_x <= e->o->xlim[1]
			&& inter_y >= e->o->ylim[0] && inter_y <= e->o->ylim[1])
		{
			e->c.inter = k;
			e->c.obj = e->o;
		}
	}
}
