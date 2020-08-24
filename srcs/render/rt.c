# include "rt.h"

static	void clear_cam_pix(t_env *e, int i)
{
	*((int *)e->data_img[0] + i) = 0;
	e->c->inter = MAX_INTER;
	e->c->obj = NULL;
}

static int	rgb_to_hexa(float *rgb)
{
	return (((int)rgb[0] << 16) + ((int)rgb[1] << 8) + (int)rgb[2]);
}

void	rt(t_env *e)
{
	int	i;

	i = -1;
	while (++i < MAX_X_CAM * MAX_Y_CAM)
	{
		clear_cam_pix(e, i);
		ray_set(e->c, i);
		inter(e);
		if (e->c->obj)
			*((int *)e->data_img[0] + i) =
				rgb_to_hexa(e->c->obj->col);
	}
}
