# include "rt.h"

static int	key_switch(int	keycode)
{
	if (keycode == ZERO)
		return (0);
	else if (keycode == UN)
		return (1);
	else if (keycode == DEUX)
		return (2);
	else if (keycode == TROIS)
		return (3);
	else if (keycode == QUATRE)
		return (4);
	else if (keycode == CINQ)
		return (5);
	else if (keycode == SIX)
		return (6);
	else if (keycode == SEPT)
		return (7);
	else if (keycode == HUIT)
		return (8);
	else if (keycode == NEUF)
		return (9);
	else if (keycode == DIX)
		return (10);
	else if (keycode == ONZE)
		return (11);
	return (-42);
}

int	expose(t_env *e)
{
	move_cam(e);
	rt(e);
//	exit(0);
	mlx_put_image_to_window(e->ptr, e->win, e->img[0], 0, 0);
	mlx_put_image_to_window(e->ptr, e->win, e->img[1], MAX_X_CAM - MAX_X_DASH, 0);
	update_dash(e);
	return (1);
}

int	key_press(int keycode, t_env *e)
{
	int	tmp;

//	printf("keycode = %d\n", keycode);
	if (keycode == EXIT)
		exit(0);
	else if ((tmp = key_switch(keycode)) != -42)
		e->move[key_switch(keycode)] = 1;
	else if (keycode == FAUCON)
		e->move[12] = MILLENIUM;
	return (1);
}

int	key(int keycode, t_env *e)
{
	int	tmp;

	if ((tmp = key_switch(keycode)) != -42)
		e->move[tmp] = 0;
	else if (keycode == FAUCON)
		e->move[12] = 1;
	return (1);
}

int	loop_hook(t_env *e)
{
	expose(e);
	return (1);
}
