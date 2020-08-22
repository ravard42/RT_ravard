# include "rt.h"

static	void clear(t_env *e, int i)
{
	*((int *)e->data_img + i) = 0;
	e->c->inter = MAX_INTER;
	e->c->obj = NULL;
}

static int	rgb_to_hexa(float *rgb)
{
	int	hexa[1];

	*hexa = 0;
	*((unsigned char *)hexa + 2) = rgb[0];
	*((unsigned char *)hexa + 1) = rgb[1];
	*((unsigned char *)hexa) = rgb[2];
	return (*hexa);
}

void	rt(t_env *e)
{
	int	i;

	i = -1;
	while (++i < MAX_X * MAX_Y)
	{
		clear(e, i);
		ray_set(e->c, i);
		inter(e);
		if (e->c->obj)
			*((int *)e->data_img + i) =
				rgb_to_hexa(e->c->obj->col);
	}
}
