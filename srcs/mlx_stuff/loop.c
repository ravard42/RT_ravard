# include "rt.h"

void	loop(t_env *e)
{
	mlx_expose_hook(e->win, &expose, e);
	mlx_hook(e->win, 2, 1L << 0, &key_press, e);
	mlx_key_hook(e->win, &key, e);
	mlx_loop_hook(e->ptr, &loop_hook, e);
	mlx_loop(e->ptr);
}
