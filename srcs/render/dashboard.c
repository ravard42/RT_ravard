#include "rt.h"

static const char	*coord[6] = {"X = ", "Y = ", "Z = ",
								"VX = ", "VY = ", "VZ = "};

/*
**	WARNING:
**	floor() function from math.h doesn't return integer portion in all cases
**	indeed it returns the nearest inferior integer!
**	so for positive float it works but for negative one it changes the integer value
**	2.5 becomes 2 whereas -2.5 becomes -3 (int8_t sign help to fix it)
*/


static void		update_cam_pos(int offset, t_env *e)
{
	char	sign;
	float	flr;
	char	*tmp[2];
	char	out[42];

	for (int i = 0; i < 3; ++i)
	{
		sign = e->c.ori[i] >= 0 ? 1 : -1; 
		flr = sign * floor(e->c.ori[i] * sign);
		tmp[0] = ft_itoa((int)flr);
		tmp[1] = ft_itoa((int)((e->c.ori[i] - flr) * sign * 10));
		ft_memset(out, 0, 20);
		
		if (!ft_strcmp(tmp[0], "0") && sign == -1)
			ft_sprintf(out, "%s-%s.%s", coord[i], tmp[0], tmp[1]);
		else
			ft_sprintf(out, "%s%s.%s", coord[i], tmp[0], tmp[1]);

		free(tmp[0]);
		free(tmp[1]);
		mlx_string_put(e->ptr, e->win, offset, (1 + i) * 20, 0x000000, out);
	}
}

static void		update_cam_dir(int offset, t_env *e)
{
	char	sign;
	float	flr;
	char	*tmp[2];
	char	out[42];

	for (int i = 0; i < 3; ++i)
	{
		sign = e->c.base[2][i] >= 0 ? 1 : -1; 
		flr = sign * floor(e->c.base[2][i] * sign);
		tmp[0] = ft_itoa((int)flr);
		tmp[1] = ft_itoa((int)((e->c.base[2][i] - flr) * sign * 10));
		ft_memset(out, 0, 20);
	
		if (!ft_strcmp(tmp[0], "0") && sign == -1)
			ft_sprintf(out, "%s-%s.%s", coord[3 + i], tmp[0], tmp[1]);
		else
			ft_sprintf(out, "%s%s.%s", coord[3 + i], tmp[0], tmp[1]);
		free(tmp[0]);
		free(tmp[1]);
		mlx_string_put(e->ptr, e->win, offset, (4 + i) * 20, 0x000000, out);
	}
}


void	update_dash(t_env *e)
{
	int		offset;

	offset = MAX_X_CAM - MAX_X_DASH + 10;
	update_cam_pos(offset, e);
	update_cam_dir(offset, e);
}
