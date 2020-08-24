#ifndef RT_H
# define RT_H


# include <stdio.h>

# include <math.h>
# include <stdlib.h>
# include <mlx.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
# include <png.h>
# include "libft.h"

# define MAX_X_CAM	500
# define MAX_Y_CAM	500
# define VP_WIDTH	1.0
# define VP_HEIGHT	1.0
# define VP_DIST	1.0
# define MAX_INTER	42000

# define MAX_X_DASH	85
# define MAX_Y_DASH	130

# define EXIT		65307
# define ZERO		119    // W : rot ↓ PITCH AXIS (assiette ou tangage) 
# define UN		115    // S : rot ↑ ...
# define DEUX		97     // A : rot ←  YAW AXIS (lacet)
# define TROIS		100    // D : rot →  ... 
# define QUATRE		113    // Q : barrel ←  ROLL AXIS (roulis)
# define CINQ		101    // E : barrel →  ...
# define SIX		65361  // ← : left
# define SEPT		65363  // → : right
# define HUIT		65364  // ↓ : back
# define NEUF		65362  // ↑ : forward
# define DIX		65438  // 0 : down
# define ONZE		32     // space : up
# define FAUCON		65505  // shift : speed


# define PAS		0.4
# define MILLENIUM	10
# define ROT		M_PI / 100

typedef struct		s_png
{
	int		width;
	int		height;
	unsigned char	color_type;
	unsigned char	bit_depth;
	unsigned char	**row_pointers;
}			t_png;

typedef struct		s_tex
{
	int		width;
	int		height;
	int		*data_t;
	float		ori[3];
	float		hori[3];
}			t_tex;

typedef struct s_obj		t_obj;

typedef struct			s_obj
{
	char		*name;
	float		ori[3];
	float		axe[3];
	float		rad;
	float		col[3];
	float		onde[3]; // (amplitude, fréquence, déphasage)
	float		xlim[2];
	float		ylim[2];
	float		spec;
	t_tex		*t;
	t_obj		*next;
}				t_obj;

typedef struct			s_cam
{
	float		ori[3];
	float		**base;
	float		ray[3];
	float		inter;
	t_obj		*obj;
}				t_cam;

typedef struct			s_env
{
	void		*ptr;
	void		*win;
	void		*img[2]; 		// second image for cam dashboard
	char		*data_img[2];	// ...
	t_cam		*c;
	t_obj		*o;
	char		move[13];
}				t_env;

void	ft_error(char *str, char *file_name);

// vect_and_mat
float	*vect_sum(float *sum, float *u, float *v);
float	*vect_sub(float *sub, float *u, float *v);
float	*vect_multi(float *multi, float k, float *u);
float	*vect_prod(float *prod, float *u, float *v);
float	dot_prod(float *u, float *v);
float	*vect_set(float *dst, float a, float b, float c);
float	*vect_copy(float *dst, float *src);
float	ft_dist(float *a, float *b);
float	*ft_norme(float *v);
float	*mat_prod(float *mp, float **mat, float *src);
int	rot(float *ez, float value, float *n);
float	**inverse(float **mat);

//parsing
void	parse(t_env *e, char *path);
float	*load_vect(float *a, char *s);

//setting
void	cam_init(t_env *e, xmlNodePtr noeud);
void	ray_set(t_cam *c, int i);
void	cam_set(t_env *e);
void	plan_set(t_env *e, xmlNodePtr noeud);
void	sphere_set(t_env *e, xmlNodePtr noeud);
void    ondePlane_set(t_env *e, xmlNodePtr noeud);

//textures
t_tex		*load_png(char *path);
void 		print_png_file(t_tex *t);


//intersection

void			inter(t_env *e);
void			plan_inter(t_env *e);
void			sphere_inter(t_env *e);
void			ondePlane_inter(t_env *e);

//pixel

void	rt(t_env *e);

//mlx_stuff

t_env	*env_init(char *path);
void init_dash(t_env *e);
void update_dash(t_env *e);
int	expose(t_env *e);
int	key_press(int keycode, t_env *e);
int	key(int keycode, t_env *e);
int	loop_hook(t_env *e);
void	loop(t_env *e);

#endif
