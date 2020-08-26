#include <rt.h>

static void	load_plan(t_env *e, xmlNodePtr noeud)
{
	xmlChar		*attr;
	
	attr = xmlGetProp(noeud, (const xmlChar *)"ori");
	load_vect(e->o->ori, (char *)attr);
	xmlFree(attr);
	attr = xmlGetProp(noeud, (const xmlChar *)"axe");
	load_vect(e->o->axe, (char *)attr);
	xmlFree(attr);
	ft_norme(e->o->axe);
	attr = xmlGetProp(noeud, (const xmlChar *)"col");
	load_vect(e->o->col, (char *)attr);
	xmlFree(attr);
	attr = xmlGetProp(noeud, (const xmlChar *)"xlim");
	load_vect(e->o->xlim, (char *)attr);
	xmlFree(attr);
	attr = xmlGetProp(noeud, (const xmlChar *)"ylim");
	load_vect(e->o->ylim, (char *)attr);
	xmlFree(attr);
	if ((noeud = noeud->children) != NULL && !ft_strcmp((const char *)noeud->name, "texture"))
	{
		attr = xmlGetProp(noeud, (const xmlChar *)"path");
		e->o->t = load_png((char *)attr);
		xmlFree(attr);
		attr = xmlGetProp(noeud, (const xmlChar *)"ori");
		load_vect(e->o->t->ori, (char *)attr);
		xmlFree(attr);
		attr = xmlGetProp(noeud, (const xmlChar *)"hori");
		load_vect(e->o->t->hori, (char *)attr);
		xmlFree(attr);
	}
}

void	plan_parser(t_env *e, xmlNodePtr noeud)
{
	t_obj		*begin;

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
	e->o->name = "plan";
	e->o->t = NULL;
	e->o->spot = 0;
	load_plan(e, noeud);
	e->o->next = NULL;
	//if (e->o->t)
	//	print_png_file(e->o->t);
	e->o = begin;
}
