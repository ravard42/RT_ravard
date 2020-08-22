#include "rt.h"

static void	cam_init_base(t_cam *c)
{
	if (c->base[2][0] == 0 && c->base[2][1] == 0)
			vect_set(c->base[0], 1, 0, 0);
	else
	{
		vect_set(c->base[0], c->base[2][1], -c->base[2][0], 0);
		ft_norme(c->base[0]);
	}
	vect_prod(c->base[1], c->base[2], c->base[0]);
}


static void	just_one_cam()
{
	ft_putstr("multi cam setting not handle\n");
	exit(0);
}

void		cam_init(t_env *e, xmlNodePtr noeud)
{
	int		i;
	xmlChar		*attr;

	if (e->c)
		just_one_cam();
	e->c = (t_cam *)malloc(sizeof(t_cam));
	attr = xmlGetProp(noeud, (const xmlChar *)"ori");
	load_vect(e->c->ori, (char *)attr);
	xmlFree(attr);
	e->c->base = (float **)malloc(sizeof(float *) * 3);
	i = -1;
	while (++i < 3)
		e->c->base[i] = (float *)malloc(sizeof(float) * 3);
	attr = xmlGetProp(noeud, (const xmlChar *)"axe");
	load_vect(e->c->base[2], (char *)attr);
	xmlFree(attr);
	ft_norme(e->c->base[2]);
	cam_init_base(e->c);
}
