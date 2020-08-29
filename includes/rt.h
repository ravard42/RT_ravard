#ifndef RT_H
# define RT_H


# include <stdio.h>

# include <math.h>
# include <stdlib.h>
# include <mlx.h>
# include <libxml/tree.h>
# include <libxml/parser.h>
# include <png.h>
# include <pthread.h>
# include <time.h>
# include "libft.h"

# define MAX_X_CAM	500
# define MAX_Y_CAM	500
# define VP_WIDTH	1.0
# define VP_HEIGHT	1.0
# define VP_DIST	1.0
# define MAX_INTER	42000
# define NB_THREAD		4

# define MAX_X_DASH	85
# define MAX_Y_DASH	130

# define EXIT		65307
# define ZERO		119    // W : rot ↓ PITCH AXIS (assiette ou tangage) 
# define UN			115    // S : rot ↑ ...
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

# define PLAN		0
# define SPHERE		1
# define WAVE		2
# define BIWAVE		3


# define PAS		0.4
# define MILLENIUM	10
# define ROT		M_PI / 45

typedef struct s_env	t_env;
typedef struct s_obj	t_obj;
typedef struct s_light	t_light;

typedef struct			s_png
{
	int					width;
	int					height;
	unsigned char		color_type;
	unsigned char		bit_depth;
	unsigned char		**row_pointers;
}						t_png;

typedef struct			s_tex
{
	int					width;
	int					height;
	int					*data_t;
	float				ori[3];
	float				hori[3];
}						t_tex;

typedef struct			s_cam
{
	float				ori[3];
	float				**base;
	float				ray[3];	// current ray
	t_obj				*obj;	// nearest object hit by ray
	float				inter;	// distance with hit
	float				m[3];	// current intersection point 
}						t_cam;

typedef struct			s_light
{
	float				ori[7]; // rot_z need 7 coord (cf move_coord directory)
	float				ray[3]; // 	normalize vector from light to current intersection point
	int8_t				move;
}						t_light;

extern void            (*move_coord[])(double time, t_light *, t_obj *);
extern float			*(*surf_normal[])(float *, t_env *);
extern void            (*surf_inter[])(t_env *);

typedef struct			s_obj
{
	uint8_t				type;
	float				ori[7]; // rot_z need 7 coord (cf move_coord directory)
	float				axe[3];
	float				nor[3]; //normal for Phong lighting model (ambiente, diffuse, specular)
	float				rad;
	float				col[3];
	float				onde[5]; // (amplitude, fréquence, φ(t), φ(0), Δφ) (cf move_coord directory)
	float				xlim[2];
	float				ylim[2];
	t_tex				*t;
	bool				spot;
	int8_t				move; // cf time_func.c
	t_obj				*next;
}						t_obj;



typedef struct			s_env
{
	void				*ptr;
	void				*win;
	void				*img[2]; 		// second image for cam dashboard
	char				*data_img[2];	// ...
	float				amb;
	double				t; 				//time 
	t_cam				c;
	t_light				l;
	t_obj				*o;
	char				move[13];
}						t_env;


void					ft_error(char *str, char *file_name);

// vect_and_mat
float					*vect_sum(float *sum, float *u, float *v);
float					*vect_sub(float *sub, float *u, float *v);
float					*vect_multi(float *multi, float k, float *u);
float					*vect_prod(float *prod, float *u, float *v);
float					dot_prod(float *u, float *v);
float					*vect_set(float *dst, float a, float b, float c);
float					*vect_copy(float *dst, float *src);
float					ft_dist(float *a, float *b);
float					*ft_norme(float *v);
float					*mat_prod(float *mp, float **mat, float *src);
int						rot(float *ez, float value, float *n);
float					**inverse(float **mat);

//init_parse
void 					init_dash(t_env *e);
void					parse(t_env *e, char *path);
float					*load_vect(float *a, char *s);

//obj_parser
void					cam_parser(t_env *e, xmlNodePtr noeud);
void					light_parser(t_env *e, xmlNodePtr noeud);
void					plan_parser(t_env *e, xmlNodePtr noeud);
void					sphere_parser(t_env *e, xmlNodePtr noeud);
void				    wave_parser(t_env *e, xmlNodePtr noeud);
void				    biwave_parser(t_env *e, xmlNodePtr noeud);

//textures
t_tex					*load_png(char *path);
void 					print_png_file(t_tex *t);


//time_func.c
void					move_map(t_env *e);

//intersection

void					inter(t_env *e);
void					plan_inter(t_env *e);
void					sphere_inter(t_env *e);
void					wave_inter(t_env *e);
void					biwave_inter(t_env *e);

//render

void					ray_set(t_cam *c, int i);
void					move_cam(t_env *e);
void					rt(t_env *e);
void				 	update_dash(t_env *e);

//mlx_stuff

t_env					*env_init(char *path);
int						expose(t_env *e);
int						key_press(int keycode, t_env *e);
int						key(int keycode, t_env *e);
int						loop_hook(t_env *e);
void					loop(t_env *e);

#endif
