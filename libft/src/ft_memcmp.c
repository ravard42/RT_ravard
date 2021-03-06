/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ravard <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 03:47:20 by ravard            #+#    #+#             */
/*   Updated: 2020/01/22 03:47:21 by ravard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char		*str1;
	unsigned char		*str2;
	size_t				i;

	if (n != 0)
	{
		str1 = (unsigned char *)s1;
		str2 = (unsigned char *)s2;
		i = -1;
		while (++i < n - 1 && str1[i] == str2[i])
			;
		return (str1[i] - str2[i]);
	}
	return (0);
}
