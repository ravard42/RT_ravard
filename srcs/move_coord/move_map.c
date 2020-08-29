#include "rt.h"

void			move_map(t_env *e)
{
	t_obj		*beg_o;

	if (e->l.move >= 0)
		move_coord[e->l.move](e->t, &e->l, NULL);
	beg_o = e->o;
	while (e->o)
	{
		if (e->o->move >= 0)
			move_coord[e->o->move](e->t, NULL, e->o);
		e->o = e->o->next;
	}
	e->o = beg_o;
}
