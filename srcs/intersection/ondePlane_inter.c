#include "rt.h"


void				ondePlane_inter(t_env *e)
{
//	float	sol;
	float	k;
	float	inter_x;
	float	inter_y;

	if (e->c->ori[2] > e->o->onde[0] && e->c->ray[2] < 0)
	{
		k = (e->o->onde[0] - e->c->ori[2]) / e->c->ray[2];
	//	if (sol >= 0 && sol <= e->c->inter)
		inter_x = e->c->ori[0] + k * e->c->ray[0];
		inter_y = e->c->ori[1] + k * e->c->ray[1];
		if (k <= e->c->inter
			&& inter_x >= e->o->xlim[0] && inter_x <= e->o->xlim[1]
			&& inter_y >= e->o->ylim[0] && inter_y <= e->o->ylim[1])
		{
			e->c->inter = k;
			e->c->obj = e->o;
		}
	}

//	if (sol >= 0 && sol <= e->c->inter)
//	{
//		e->c->inter = sol;
//		e->c->obj = e->o;
//	}
}
