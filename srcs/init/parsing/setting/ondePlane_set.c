#include <rt.h>

static void	load_ondePlane(t_env *e, xmlNodePtr noeud)
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
	attr = xmlGetProp(noeud, (const xmlChar *)"spec");
	load_vect(&e->o->spec, (char *)attr);
	xmlFree(attr);
}

void	ondePlane_set(t_env *e, xmlNodePtr noeud)
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
	e->o->name = "ondePlane";
	load_ondePlane(e, noeud);
	e->o->next = NULL;
	e->o = begin;
}
