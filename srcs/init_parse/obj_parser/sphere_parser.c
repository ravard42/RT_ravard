#include <rt.h>

static void	load_sphere(t_env *e, xmlNodePtr noeud)
{
	xmlChar		*attr;
	
	attr = xmlGetProp(noeud, (const xmlChar *)"ori");
	load_vect(e->o->ori, (char *)attr);
	xmlFree(attr);
	attr = xmlGetProp(noeud, (const xmlChar *)"rad");
	e->o->rad = ft_atof((char *)attr);
	xmlFree(attr);
	attr = xmlGetProp(noeud, (const xmlChar *)"col");
	load_vect(e->o->col, (char *)attr);
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

void	sphere_parser(t_env *e, xmlNodePtr noeud)
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
	e->o->type = SPHERE;
	e->o->move = -1;
	load_sphere(e, noeud);
	e->o->next = NULL;
	e->o = begin;
}
