# include "rt.h"

void		ray_set(t_cam *c, int i)
{
	float	tmp[3];

	tmp[0] = -1 * VP_WIDTH / 2 + i % MAX_X * VP_WIDTH / MAX_X;
	tmp[1] = -1 * VP_HEIGHT / 2 + i / MAX_Y * VP_HEIGHT / MAX_Y;
	tmp[2] = VP_DIST;
	ft_norme(tmp);
	mat_prod(c->ray, c->base, tmp);
}

static void	cam_rot(t_env *e)
{
	if (e->move[0] && rot(e->c->base[2], -ROT, e->c->base[0]))
		vect_prod(e->c->base[1], e->c->base[2], e->c->base[0]);
	if (e->move[1] && rot(e->c->base[2], ROT, e->c->base[0]))
		vect_prod(e->c->base[1], e->c->base[2], e->c->base[0]);
	if (e->move[2] && rot(e->c->base[2], -ROT, e->c->base[1]))
		vect_prod(e->c->base[0], e->c->base[1], e->c->base[2]);
	if (e->move[3] && rot(e->c->base[2], ROT, e->c->base[1]))
		vect_prod(e->c->base[0], e->c->base[1], e->c->base[2]);
	if (e->move[4] && rot(e->c->base[0], -ROT, e->c->base[2]))
		vect_prod(e->c->base[1], e->c->base[2], e->c->base[0]);
	if (e->move[5] && rot(e->c->base[0], ROT, e->c->base[2]))
		vect_prod(e->c->base[1], e->c->base[2], e->c->base[0]);
}

static void	cam_shift(t_env *e)
{
	float	tmp[3];
	
	if (e->move[6])
		vect_sub(e->c->ori, e->c->ori, vect_multi(tmp, e->move[12] * PAS, e->c->base[0]));
	if (e->move[7])
		vect_sum(e->c->ori, e->c->ori, vect_multi(tmp, e->move[12] * PAS, e->c->base[0]));
	if (e->move[8])
		vect_sub(e->c->ori, e->c->ori, vect_multi(tmp, e->move[12] * PAS, e->c->base[2]));
	if (e->move[9])
		vect_sum(e->c->ori, e->c->ori, vect_multi(tmp, e->move[12] * PAS, e->c->base[2]));
	if (e->move[10])
		vect_sum(e->c->ori, e->c->ori, vect_multi(tmp, e->move[12] * PAS, e->c->base[1]));
	if (e->move[11])
		vect_sub(e->c->ori, e->c->ori, vect_multi(tmp, e->move[12] * PAS, e->c->base[1]));
}

void	cam_set(t_env *e)
{
	cam_shift(e);
	cam_rot(e);
}
