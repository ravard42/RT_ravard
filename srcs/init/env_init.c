# include "rt.h"

static void init_dash_color(t_env *e)
{
	int	i;

	i = -1;
	while (++i < MAX_X_DASH * MAX_Y_DASH)
		*((int *)e->data_img[1] + i) = 0xbbbbbb;
}

t_env		*env_init(char *path)
{
	t_env	*e;
	int	info[3];
	int	i;

	e = (t_env *)malloc(sizeof(t_env));
	e->ptr = mlx_init();
	e->win = mlx_new_window(e->ptr, MAX_X_CAM, MAX_Y_CAM, "RT");
	e->img[0] = mlx_new_image(e->ptr, MAX_X_CAM, MAX_Y_CAM);
	e->data_img[0] = mlx_get_data_addr(e->img[0], info, info + 1, info + 2);
	e->img[1] = mlx_new_image(e->ptr, MAX_X_DASH, MAX_Y_DASH);
	e->data_img[1] = mlx_get_data_addr(e->img[1], info, info + 1, info + 2);
	e->c = NULL;
	e->o = NULL;
	i = -1;
	while (++i < 12)
		e->move[i] = 0;
	e->move[12] = 1;
	parse(e, path);
	if (!e->c)
		ft_error("aucune config cam en entree\n", NULL);
	init_dash_color(e);
	return (e);
}
