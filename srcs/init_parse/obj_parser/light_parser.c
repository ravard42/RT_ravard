#include "rt.h"

static void	load_light(t_env *e, xmlNodePtr noeud)
{
	xmlChar		*attr;
	
	attr = xmlGetProp(noeud, (const xmlChar *)"ori");
	load_vect(e->l.ori, (char *)attr);
	xmlFree(attr);
}

void		light_parser(t_env *e, xmlNodePtr noeud)
{
	load_light(e, noeud);
}
