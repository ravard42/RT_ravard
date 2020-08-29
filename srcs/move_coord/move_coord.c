#include "rt.h"

/*
** 	for rotative points, there are 5 coordinates for ori attribute set like this:
** 	M(t) = [xt, yt, zo, xo, yo, r, f]
**	ou xo, yo, zo represent the origin of the circle 
**	r the radius and f the frequency
*/

static void		rot_z(double t, t_light *l, t_obj *o)
{
	float	*x;

	x = (l) ? l->ori : o->ori;
	vect_set(x, x[3] + x[5] * cos(2 * M_PI * x[6] * t), x[4] + x[5] * sin(2 * M_PI * x[6] * t), x[2]);
}

/*
** cycleTranslation plan ori attribute need 6 coordinates
** M(t) = [xo, yo, zt, zo, r, f]
** xo, yo, zo represent the original position of a point on the plan
** zt the actual position of the plan on z axis depending on time
** r the amplitude of the translation and f the frequency
*/

static void		cycleTrans_z(double t, t_light *l, t_obj *o)
{
	float	*x;

	x = (l) ? l->ori : o->ori;
	x[2] = x[3] + x[4] * cos(2 * M_PI * x[5] * t);
}

/*
** wave_t need 5 onde attribute coordinates
** M(t) = [A, ω, φ(t), φ(0), Δφ]
** where φ(t), φ(0), Δφ reprensent respectively
** φ(t) dephasing at time t
** φ(0) initial dephasing
** Δφ dephasing variation frequency
*/

static void		wave_t(double t, t_light *l, t_obj *o)
{
	float	*x;	

	(void)l;
	x = o->onde;
	x[2] = x[3] + 2 * M_PI * x[4] * t;
}

void            (*move_coord[])(double, t_light *, t_obj *) = {rot_z, cycleTrans_z, wave_t};
