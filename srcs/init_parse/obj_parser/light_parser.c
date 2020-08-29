#include "rt.h"

static void	load_light(t_env *e, xmlNodePtr noeud)
{
	xmlChar		*attr;
	
	attr = xmlGetProp(noeud, (const xmlChar *)"ori");
	load_vect(e->l.ori, (char *)attr);
	xmlFree(attr);
	if ((attr = xmlGetProp(noeud, (const xmlChar *)"move_coord")))
	{
		e->l.move = ft_atoi((char *)attr);
		xmlFree(attr);
	}
}

void		light_parser(t_env *e, xmlNodePtr noeud)
{
	e->l.move = -1;
	load_light(e, noeud);
}
