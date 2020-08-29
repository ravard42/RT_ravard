# include "rt.h"

static	void 		clear_cam_pix(t_env *e, int i)
{
	*((int *)e->data_img[0] + i) = 0;
	e->c.inter = MAX_INTER;
	e->c.obj = NULL;
}

static int	pix_set(t_env *e)
{
	float	diff;
	float	nor[3];
	float	ret[3];

	surf_normal[e->c.obj->type](nor, e);	
	diff = e->c.obj->spot ? 2 - e->amb : fabs(dot_prod(nor, e->l.ray));
	vect_multi(ret, (e->amb + diff) / 2, e->c.obj->col);
	return ((((int)ret[0]) << 16) + (((int)ret[1]) << 8) + ((int)ret[2]));
}

typedef struct		s_data_th
{
	uint8_t			id;
	int				n;
	t_env			e;
}					t_data_th;


void	*render_chunk(void *arg)
{
	t_env		*e;
	int			id;
	int			chunk_len;
	int			i;

	e = &((t_data_th *)arg)->e;
	id = ((t_data_th *)arg)->id;
	chunk_len = ((t_data_th *)arg)->n;
	i = id * chunk_len;
	while (i < (id + 1) * chunk_len)
	{
		clear_cam_pix(e, i);
		ray_set(&e->c, i);
		inter(e);
		if (e->c.obj)
		{
			vect_multi(e->c.m, e->c.inter, e->c.ray);	// compute current intersection point M(mx,my,mz)
			vect_sum(e->c.m, e->c.ori, e->c.m);			// ...
			vect_sub(e->l.ray, e->c.m, e->l.ori);		// compute light ray normalized vector (from e->l->or to M)
			ft_norme(e->l.ray);						// ... 
			*((int *)e->data_img[0] + i) = pix_set(e);
		}
		++i;
	}
	return (NULL);
}

static void		write_chunck(t_env *dst, t_env *src, uint8_t id, int n)
{
	int		i;

	for (i = id * n; i < (id + 1) * n; ++i)
		*((int *)dst->data_img[0] + i) = *((int *)src->data_img[0] + i);
}

void	rt(t_env *e)
{
	int			chunk_len;
	int			i;
	pthread_t   th[NB_THREAD];
	t_data_th	data[NB_THREAD];

	chunk_len = MAX_X_CAM * MAX_Y_CAM / NB_THREAD;
	for(i=0; i < NB_THREAD; i++)
	{
		data[i].id = i;
		data[i].n = chunk_len;
		ft_memcpy(&data[i].e, e, sizeof(*e));
		pthread_create(th + i, NULL, render_chunk, data + i);
	}
	i = -1;
	while (++i < NB_THREAD)
		pthread_join(th[i], NULL);
	i = -1;
	while (++i < NB_THREAD)
		write_chunck(e, &data[i].e, i, chunk_len);
}	
