# include "rt.h"

void	parse(t_env *e, char *path)
{
	xmlDocPtr 	doc;
	xmlNodePtr 	noeud;

    	xmlKeepBlanksDefault(0); // Ignore les noeuds texte composant la mise en forme
    	doc = xmlParseFile(path);
	if (doc == NULL)
		ft_error("Document XML invalide\n", NULL);
	noeud = xmlDocGetRootElement(doc);
	if (noeud == NULL || (noeud = noeud->children) == NULL) 
	{
		ft_error("Document XML invalide\n", NULL);
		xmlFreeDoc(doc);
	}
	while (noeud)
	{
		if (!ft_strcmp((const char *)noeud->name, "cam"))
			cam_parser(e, noeud);
		else if (!ft_strcmp((const char *)noeud->name, "plan"))
			plan_parser(e, noeud);
		else if (!ft_strcmp((const char *)noeud->name, "sphere"))
			sphere_parser(e, noeud);
		else if (!ft_strcmp((const char *)noeud->name, "wave"))
			wave_parser(e, noeud);
		else if (!ft_strcmp((const char *)noeud->name, "biwave"))
			biwave_parser(e, noeud);
		noeud = noeud->next;
	}
	xmlFreeDoc(doc);
}