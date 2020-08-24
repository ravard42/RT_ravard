#include "rt.h"

static void		set_param(float *param, t_env *e)
{
	param[0] = pow(e->c->ray[0], 2)
		+ pow(e->c->ray[1], 2)
		+ pow(e->c->ray[2], 2);
	param[1] = 2 * (e->c->ray[0]
			* (e->c->ori[0] - e->o->ori[0])
			+ e->c->ray[1] * (e->c->ori[1]
				- e->o->ori[1]) + e->c->ray[2]
			* (e->c->ori[2] - e->o->ori[2]));
	param[2] = pow(e->c->ori[0]
			- e->o->ori[0], 2) + pow(e->c->ori[1]
				- e->o->ori[1], 2) + pow(e->c->ori[2]
					- e->o->ori[2], 2) - pow(e->o->rad, 2);
}

static float	solve(float *param)
{
	float	delt;
	float	tmp[2];
	float	sol;

	sol = -42;
	if ((delt = pow(param[1], 2) - 4 * param[0] * param[2]) >= 0)
	{
		tmp[0] = (-param[1] + sqrt(delt)) / (2 * param[0]);
		tmp[1] = (-param[1] - sqrt(delt)) / (2 * param[0]);
		if ((tmp[0] >= 0 && tmp[1] < 0)
				|| (tmp[1] >= 0 && tmp[0] < 0))
			sol = (tmp[0] >= 0) ? tmp[0] : tmp[1];
		else if (tmp[0] >= 0 && tmp[1] >= 0)
			sol = (tmp[0] <= tmp[1]) ? tmp[0] : tmp[1];
	}
	return (sol);
}

/*
** rappel : e->c->ray est le vecteur directeur du rayon
**
** idée :
** soit k une variable réelle
** on fait varier k et on regarde si le point 
** M = e->c->ori + k * e->c->ray appartient à notre surface.
** i-e si ses coordonnées verifient l'équation de la sphere dans le cas présent.
*/

void				sphere_inter(t_env *e)
{
	float	param[3];
	float	sol;

	set_param(param, e);
	sol = solve(param);
	if (sol >= 0 && sol <= e->c->inter)
	{
		e->c->inter = sol;
		e->c->obj = e->o;
	}
}
