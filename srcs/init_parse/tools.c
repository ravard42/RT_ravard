/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 19:29:17 by ravard            #+#    #+#             */
/*   Updated: 2017/02/26 19:44:16 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_error(char *str, char *file_name)
{
	ft_putstr(2, str);
	if (file_name)
	{
		ft_putstr(2, file_name);
		ft_putstr(2, " introuvalble\n");
	}
	exit(0);
}

static char		**is_valid_coord(int *dim, char *str)
{
	int		len;
	int		i;
	int		k;
	char	**str_coord;

	len = ft_strlen(str);
	if (!(str[0] == '{' && str[len - 1] == '}' && str[len] == '\0'))
		ft_error("xml param bad format\n", NULL);
	i = -1;
	k = 0;
	while (str[++i])
		if (str[i] == ',')
			k++;
	*dim = k + 1;
	str = ft_revstr(ft_revstr(str + 1) + 1);
	str_coord = ft_strsplit(str, ',');
	i = -1;
	while (++i < k + 1)
		if (!str_coord || !ft_is_float(str_coord[i]))
			ft_error("xml param bad format (need float values)\n", NULL);
	return (str_coord);
}

float	*load_vect(float *a, char *s)
{
	char	**str_coord;
	int		dim;
	int		i;

	if (!(s && (str_coord = is_valid_coord(&dim, s))))
		ft_error("xml param parsing error\n", NULL);
	if (!a)
		a = (float *)malloc(sizeof(float) * 3);	
	for (i = 0; i < dim; ++i)
		a[i] = ft_atof(str_coord[i]);
	free_split(str_coord);
	return (a);
}
