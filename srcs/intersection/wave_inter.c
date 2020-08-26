#include "rt.h"

#define COND_0 (e->c.ori[2] > e->o->onde[0] && e->c.ray[2] < 0)
#define DK			0.1
#define TOL			0.1
#define ITER_MAX	1000

/*
**	unicodes:
**	θ : 03b8
**	ω : 03c9
**	π : 03c0
**	φ : 03c6
**
**	on note:
**	1)en minuscule pour les scalaires
**	2)en majuscule quand plusieurs dimensions
**	3)avec un prefix v pour les vecteurs 
**	
**	a=e->o->onde[0] l'amplitude de l'onde
**	ω=2πf ou f=e->o->onde[1], la fréquence de l'onde
**	φ=e->o->onde[2], le déphasage de l'onde
**	C(cx, cy, cz)=e->c.cam l'origine de la cam
**	vX(1,0,0), vY(0,1,0) et vZ(0, 0, 1) les vecteurs du repère
**	vR(rx, ry, rz)=e->c.ray le rayon considéré
**
**	IMPORTANT : on a choisit de representer uniquement des 'wave' (onde plane) centrées en z=0
**				et orientées suivant vX
**
**	idée:
**	a] visualiser l'onde plane prise en sandwich entre 2 plans d'équations z=+A et z=-A
**		pour faciliter les choses on placera la cam au dessus et considerera uniquement z=+A
**	b] COND_0 assure que le rayon intersecte bien le plan supérieur en un point N(xn, yn, zn)
**	c] on cherche k_0 \ C + k_0 * vR = N
**		cos = adj/ hyptonesuse donc en posant θ l'ange entre vR et -vZ
**		on a cos(θ)= cz-a/k_0
**		or par la formule du produit scalaire vR.(-vZ) = |vR||vZ|cos(θ) = rx*0 + ry*0 - rz*1
**		vR et vZ étant normé on obtient cos(θ)=-rz*z
**		d'où k_0 = a-cz/rz
**	d] posons à présent l'équation (E) paramétrique de notre wave
**		
**		(E)
**		soit (u,v) dans R
**		x=u \ xlim[0]<u<xlim[1]
**		y=v \ ylim[0]<v<ylim[1]
**		z=a*cos(ω*u + φ)
**
**		on voit que v est indépendant des deux autres, il doit seulement être borné
**		en revanche u témoigne de la interdépendance des variables x et z.
**		
**	e] ce qui nous interesse est de savoir si l'on peut trouver un point M sur notre rayon qui vérifie (E)
**		On cherche donc k tel que C + k * vR = M(xm, ym, zm)
**
**		Dans un premier temps nous allons considérer que l'onde s'étend à l'infini en x et y
**		On cherche alors la plus petite solution (qui existe si COND_0) puis l'on reviendra à xlim et ylim ensuite.
**		Puisque l'onde est maintenant infini il suffit de chercher la solution en x et z (aucune contrainte sur y)
**		En mettant M dans (E) on obtient donc cz + k*rz = a*cos(ω*(cx + k*rx) + φ)
**		On pose maintenant g(k) = k*rz - a*cos(ω*(cx + k*rx) + φ) + cz
**		Le problème se réduit à résoudre g(k) = 0
**		En faisant un changement de variable on voit que l'équation  est de la forme cos(x) = ax + b
**		Ce type d'équation n'admettant pas de solution algébrique, on va y aller par tatonnement.
**		
**		On sait que g(k_0 - 0.01) n'est pas une solution puisqu'au dessus du plan tangent supérieur
**		On redéfinit k_0 : k_0 = a-cz/rz - 0.01
**		Tant que |g(k_i)| ne passe pas sous la valeur de TOL on calcule g(k_i+1) où k_i+1 = k_i + DK
**		Cela a du sens de par la continuité de g!
**		Une fois qu'on a une solution approximative on calcule les coordonnées de M=C + k * vR
**		et on voit si cette solution est acceptable relativement à xlim et ylim.
**		Si oui c'est fini sinon pas de solution
**
**		NB: jouer avec les valeurs de TOL et DK pour obtenir un bon rapport render/compute_time
**
**
*/


static float		g(float k, float *param)
{
	return (k * param[6] - param[0] * cos(param[1] * (param[3] + k * param[5]) + param[2]) + param[4]);
}

/*
** 	param:
**	0 : a
**	1 : ω
**	2 : φ
**	3 : cx
**	4 : cz
**	5 : rx
**	6 : rz
*/


void				wave_inter(t_env *e)
{
	float	i;
	float	k;
	float	param[7];
	float	inter_x;
	float	inter_y;

	if COND_0
	{
		i = -1;
		k = (e->o->onde[0] - e->c.ori[2]) / e->c.ray[2] - 0.01;
		param[0] = e->o->onde[0];
		param[1] = 2 * M_PI * e->o->onde[1];
		param[2] = e->o->onde[2];
		param[3] = e->c.ori[0];
		param[4] = e->c.ori[2];
		param[5] = e->c.ray[0];
		param[6] = e->c.ray[2];
		while (fabs(g(k, param)) > TOL && ++i < ITER_MAX)
			k += DK;
		inter_x = e->c.ori[0] + k * e->c.ray[0];
		inter_y = e->c.ori[1] + k * e->c.ray[1];
		if (k <= e->c.inter
			&& inter_x >= e->o->xlim[0] && inter_x <= e->o->xlim[1]
			&& inter_y >= e->o->ylim[0] && inter_y <= e->o->ylim[1])
		{
			e->c.inter = k;
			e->c.obj = e->o;
		}
	}
}
