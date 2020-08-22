#include "rt.h"

void			inter(t_env *e)
{
	t_obj	*begin;

	begin = e->o;
	while (e->o != NULL)
	{
		if (!ft_strcmp("plan", e->o->name))
			plan_inter(e);
		else if (!ft_strcmp("sphere", e->o->name))
			sphere_inter(e);
		e->o = e->o->next;
	}
	e->o = begin;
}
