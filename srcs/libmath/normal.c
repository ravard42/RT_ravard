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

static float		*wave_normal(float *ret, t_env *e)
{
	(void)e;
	vect_set(ret, 0, 0, 0);
	return (NULL);
}

static float		*biwave_normal(float *ret, t_env *e)
{
	(void)e;
	vect_set(ret, 0, 0, 0);
	return (NULL);
}

t_normal normal[] = {
		{"plan", plan_normal},
		{"sphere", sphere_normal},
		{"wave", wave_normal},
		{"biwave", biwave_normal},
		{NULL, NULL}
};
