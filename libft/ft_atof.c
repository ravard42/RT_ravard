/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 21:31:53 by ravard            #+#    #+#             */
/*   Updated: 2017/02/26 21:32:55 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_float(char *s)
{
	int	i;
	int	k;

	if (!s || !((s[0] == '-' && s[1] != '\0') || (s[0] >= '0' && s[0] <= '9')))
	{
		ft_putstr("libft->ft_atof : is not a float\n");
		exit(0);
	}
	k = 0;
	i = 0;
	while (s[++i])
		if (!((s[i] >= '0' && s[i] <= '9')
					|| (s[i] == '.' && (k += 1) < 2)))
		{
			ft_putstr("libft->ft_atof : is not a float\n");
			exit(0);
		}
	return (1);
}

float		ft_atof(char *s)
{
	char	**tmp;
	int		len;
	float	pmt;
	float	ret;

	if (s && s[0])
		if (!is_float(s))
			return (0);
	tmp = ft_strsplit(s, '.');
	if (tmp[1])
		len = ft_strlen(tmp[1]);
	ret = 0;
	ret = tmp[1] ? (float)ft_atoi(tmp[1]) / ft_power(10, len) : 0;
	pmt = (float)ft_atoi(tmp[0]);
	ret = (pmt > 0) ? ret + pmt : pmt - ret;
	free(tmp[0]);
	free(tmp[1]);
	free(tmp);
	return (ret);
}
