#include "rt.h"

float	*vect_sum(float *sum, float *u, float *v)
{
	sum[0] = u[0] + v[0];
	sum[1] = u[1] + v[1];
	sum[2] = u[2] + v[2];
	return (sum);
}

float	*vect_sub(float *sub, float *u, float *v)
{
	sub[0] = u[0] - v[0];
	sub[1] = u[1] - v[1];
	sub[2] = u[2] - v[2];
	return (sub);
}

float	*vect_multi(float *multi, float k, float *u)
{
	multi[0] = k * u[0];
	multi[1] = k * u[1];
	multi[2] = k * u[2];
	return (multi);
}

/*
** *prod must be different of *u and *v inputs here
*/

float	*vect_prod(float *prod, float *u, float *v)
{
	prod[0] = u[1] * v[2] - u[2] * v[1];
	prod[1] = u[2] * v[0] - u[0] * v[2];
	prod[2] = u[0] * v[1] - u[1] * v[0];
	return (prod);
}

float	dot_prod(float *u, float *v)
{
	float	tmp;

	tmp = u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
	return (tmp);
}
