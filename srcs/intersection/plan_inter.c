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
	float	sol;

	if (dot_prod(e->o->axe, e->c.ray))
	{
		sol = solve(e);
		if (sol >= 0 && sol <= e->c.inter)
		{
			e->c.inter = sol;
			e->c.obj = e->o;
		}
	}
}
