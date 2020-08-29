#include "rt.h"

void            (*surf_inter[])(t_env *e) = {
				plan_inter,
				sphere_inter,
				wave_inter,
				biwave_inter
};

void			inter(t_env *e)
{
	t_obj	*begin;

	begin = e->o;
	while (e->o != NULL)
	{
		surf_inter[e->o->type](e);
		e->o = e->o->next;
	}
	e->o = begin;
}
