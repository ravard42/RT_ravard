#include "rt.h"

static float		*plan_normal(float *ret, t_env *e)
{
	vect_copy(ret, e->c.obj->axe);
//	if (dot_prod(e->c.ray, e->l.ray) <= 0) // to avoid enlightement of the dark side
//	{										//(doesn't work, find another way)	
//		printf("COUCOU\n");
//		vect_set(ret, 0, 0, 0);
//	}
	return (ret);
}

static float		*sphere_normal(float *ret, t_env *e)
{
	vect_sub(ret, e->c.m, e->c.obj->ori);
	ft_norme(ret);
	if (dot_prod(ret, e->l.ray) >= 0)
		vect_set(ret, 0, 0, 0);
	return (ret);
}

/*
**	unicode:
**	∂ : 2202
**	² : 00b2
**	³ : 00b3
**	₀ : 2080
**
**	on rappelle le système d'équations paramétriques (E) de notre surface (S)
**	(E)
**	soit (u,v) dans R
**	x=u \ xlim[0]<u<xlim[1]
**	y=v \ ylim[0]<v<ylim[1]
**	z=a*cos(ω*u + φ)
**
**	on pose
**	(f)
**	R² 		-> 	R³
**	(u, v)		f(u, v) = (u, v, a*cos(ω*u + φ))
**
**	les dérivés partielles étant continues sur R²
**	on en conclut que f est C¹ sur R² et donc différentiable sur R²
**	on pose:
**	tan_u(u, v) = ∂f/∂u = (∂u/∂u, ∂v/∂u, ∂a*cos(ω*u + φ)/∂u)
**	tan_v(u, v) = ∂f/∂u = (∂u/∂v, ∂v/∂v, ∂a*cos(ω*u + φ)/∂v)
**
**	tan_u(u, v) = (1, 0, -aω*sin(ω*u + φ))
**	tan_v(u, v) = (0, 1, 0)
**
**	M₀(u₀, v₀) un point sur S
**	tan_u(u₀, v₀) et tan_v(u₀, v₀) sont dans le plan tangent à S et non colinéaires
**	la normale à S en M₀ est donc |tan_u(u₀, v₀)|^|tan_v(u₀, v₀)|
**	CQFD
*/			

static float		*wave_normal(float *ret, t_env *e)
{
	float tan_u[3];
	float tan_v[3];
	float c[3];

	for(int i = 0; i < 3; i++)
		c[i] = e->o->onde[i];

	vect_set(tan_u, 1, 0, -c[0] * c[1] * sin(c[0] * e->c.m[0] + c[2]));
	vect_set(tan_v, 0, 1, 0);
	ft_norme(tan_u);
	ft_norme(tan_v);
	vect_prod(ret, tan_u, tan_v);	
	return (ret);
}

static float		*biwave_normal(float *ret, t_env *e)
{
	float tan_u[3];
	float tan_v[3];
	float c[3];

	for(int i = 0; i < 3; i++)
		c[i] = e->o->onde[i];

	vect_set(tan_u, 1, 0, -c[0] * c[1] * sin(c[0] * e->c.m[0] + c[2]));
	vect_set(tan_v, 0, 1, -c[0] * c[1] * sin(c[0] * e->c.m[1] + c[2]));
	ft_norme(tan_u);
	ft_norme(tan_v);
	vect_prod(ret, tan_u, tan_v);	
	return (ret);
}

float				*(*surf_normal[])(float *, t_env *) = {
					plan_normal,
					sphere_normal,
					wave_normal,
					biwave_normal
};
