#include <rt.h>

static void	load_biwave(t_env *e, xmlNodePtr noeud)
{
	xmlChar		*attr;
	
	attr = xmlGetProp(noeud, (const xmlChar *)"ori");
	load_vect(e->o->ori, (char *)attr);
	xmlFree(attr);
	attr = xmlGetProp(noeud, (const xmlChar *)"col");
	load_vect(e->o->col, (char *)attr);
	xmlFree(attr);
	attr = xmlGetProp(noeud, (const xmlChar *)"onde");
	load_vect(e->o->onde, (char *)attr);
	xmlFree(attr);
	attr = xmlGetProp(noeud, (const xmlChar *)"xlim");
	load_vect(e->o->xlim, (char *)attr);
	xmlFree(attr);
	attr = xmlGetProp(noeud, (const xmlChar *)"ylim");
	load_vect(e->o->ylim, (char *)attr);
	xmlFree(attr);
	attr = xmlGetProp(noeud, (const xmlChar *)"spot");
	e->o->spot = attr ? 1 : 0;	
	xmlFree(attr);
	if ((attr = xmlGetProp(noeud, (const xmlChar *)"move_coord")))
	{
		e->o->move = ft_atoi((char *)attr);
		xmlFree(attr);
	}
}

void	biwave_parser(t_env *e, xmlNodePtr noeud)
{
	t_obj	*begin;

	if (e->o == NULL)
	{
		e->o = (t_obj *)malloc(sizeof(t_obj));
		begin = e->o;
	}
	else
	{
		begin = e->o;
		while (e->o->next != NULL)
			e->o = e->o->next;
		e->o->next = (t_obj *)malloc(sizeof(t_obj));
		e->o = e->o->next;
	}
	e->o->type = BIWAVE;
	e->o->move = -1;
	load_biwave(e, noeud);
	e->o->next = NULL;
	e->o = begin;
}
