#include "rt.h"

float	*vect_set(float *dst, float a, float b, float c)
{
	if (dst == NULL)
		dst = (float *)malloc(sizeof(float) * 3);
	dst[0] = a;
	dst[1] = b;
	dst[2] = c;
	return (dst);
}

float	*vect_copy(float *dst, float *src)
{
	dst[0] = src[0];
	dst[1] = src[1];
	dst[2] = src[2];
	return (dst);
}

float	ft_dist(float *a, float *b)
{
	float	tmp;

	tmp = sqrt(pow(b[0] - a[0], 2)
		+ pow(b[1] - a[1], 2)
		+ pow(b[2] - a[2], 2));
	return (tmp);
}

float	*ft_norme(float *v)
{
	float	tmp;

	if (v[0] == 0 && v[1] == 0 && v[2] == 0)
	{
		ft_putstr(2, "on ne peut pas normer le vecteur NULL!\n");
		exit(0);
	}
	tmp = sqrt(pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2));
	v[0] = v[0] / tmp;
	v[1] = v[1] / tmp;
	v[2] = v[2] / tmp;
	return (v);
}
