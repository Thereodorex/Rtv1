/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcorwin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:25:54 by jcorwin           #+#    #+#             */
/*   Updated: 2019/02/22 20:22:15 by jcorwin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <SDL.h>
# include <math.h>
# include "get_next_line.h"
# include "libft.h"

# define WIDTH 1920
# define HEIGHT 1080
# define STOP exit(0);
# define MAX_SOURCE_SIZE (0x100000)

typedef struct	s_k
{
	double k1;
	double k2;
	double k3;
}				t_k;

typedef enum	e_light_type
{
	ambient = 0,
	point,
	direct
}				t_light_type;

typedef struct	s_vec
{
	double		x;
	double		y;
	double		z;
}				t_vec;

typedef struct	s_quat
{
	double		w;
	double		x;
	double		y;
	double		z;
}				t_quat;

typedef struct	s_light
{
	t_light_type	type;
	double			intens;
	t_vec			pos;
	t_vec			dir;
}				t_light;

typedef struct	s_img
{
	int				w;
	int				h;
	unsigned int	*img;
}				t_img;

typedef struct	s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*tex;
	SDL_Surface		*surf;
	t_img			img;
}				t_sdl;

typedef struct	s_ray
{
	t_vec	cam;
	t_vec	scene;
	double	cos_a;
	double	cos_b;
	t_vec	ray;
	t_vec	ray2;
}				t_ray;

typedef struct	s_screen
{
	t_vec		cor;
	t_vec		hor;
	t_vec		ver;
}				t_screen;

typedef struct	s_plane
{
	t_vec			point;
	t_vec			norm;
	unsigned int	color;
	double			specular;
}				t_plane;

typedef struct	s_sphere
{
	t_vec			cen;
	double			rad;
	unsigned int	color;
	double			specular;
}				t_sphere;

typedef struct	s_cone
{
	t_vec			cen;
	t_vec			dir;
	double			cos;
	double			specular;
	unsigned int	color;
}				t_con;

typedef struct	s_cylinder
{
	t_vec			cen;
	double			rad;
	t_vec			dir;
	double			specular;
	unsigned int	color;
}				t_cyl;

typedef struct	s_param
{
	t_ray		ray;
	t_screen	scr;
	t_vec		cam;
	int			plane_count;
	int			sp_count;
	int			l_count;
	int			cyl_count;
	int			con_count;
	t_sphere	*sp;
	t_light		*l;
	t_con		*con;
	t_cyl		*cyl;
	t_plane		*plane;
}				t_param;

typedef struct	s_figure
{
	unsigned int	color;
	t_vec			p;
	t_vec			norm_vec;
	double			specular;
}				t_figure;

typedef struct	s_ren_light
{
	t_vec	light_ray;
	double	intensity;
	t_vec	r;
	double	n_dot_l;
	double	r_dot_v;
}				t_ren_light;

typedef struct	s_intersection
{
	t_k		k;
	double	t1;
	double	t2;
	double	dis;
	double	p;
	int		i;
	t_vec	oc;
}				t_intersection;

typedef struct	s_intersection2
{
	t_param		*param;
	t_vec		ray;
	double		t_min;
	double		t_max;
	t_vec		source;
}				t_intersection2;

t_vec			vec_new(double x, double y, double z);
t_vec			vec_frompoint(t_vec p1, t_vec p2);
t_vec			vec_sum(t_vec v1, t_vec v2);
t_vec			vec_mult(double a, t_vec vec);
double			vec_scal(t_vec v1, t_vec v2);
double			vec_len(t_vec v);
t_vec			ray_par(t_ray r, double t);
t_vec			vec_plus(double a, t_vec res);
t_vec			vec_unit(t_vec v);

void			trace_sphere(t_sdl *sdl, t_param *p);

int				render(t_sdl *sdl, t_param *param,
							double angle1, double angle2);

void			sdl_img_init(t_img *img, int w, int h);
void			sdl_img_destroy(t_img *img);
t_sdl			*sdl_init(int x, int y, int w, int h);
void			*sdl_destroy(t_sdl *sdl);
void			sdl_print(t_sdl *sdl);

void			sdl_img_cpy(t_sdl *sdl, t_img *img, int x, int y);
void			sdl_putpix(t_sdl *sdl, int x, int y, unsigned int color);

void			gnl(int fd, char **line);
void			get_cam(t_param *p, int fd, char **line);
void			get_light(t_param *p, int fd, char **line);

void			cam_init(t_param *param);
void			read_file(t_param *p, char *filename);
int				catch_event(t_param *p, t_sdl *sdl, SDL_Event *event);
void			go(t_sdl *sdl, t_param *param);

double			get_double(char *line);
t_vec			get_vec(char *line);
char			*get_word(char *line);

void			l_real(t_param *p);
void			sp_real(t_param *p);
void			con_real(t_param *p);
void			cyl_real(t_param *p);
void			plane_real(t_param *p);
unsigned int	color_with_light(t_param *param, t_vec ray, t_figure sphere);
void			intersection_with_cone(t_figure *sphere,\
				double *t, t_intersection2 j);
void			intersection_with_sphere(t_figure *sphere,\
				double *t, t_intersection2 j);
void			intersection_with_cylinder(t_figure *sphere,\
				double *t, t_intersection2 j);
void			intersection_with_plane(t_figure *sphere,\
				double *t, t_intersection2 j, int i);
t_vec			vec_cross(t_vec v1, t_vec v2);
t_quat			quat_invert(t_quat q);
t_quat			quat_scale(t_quat q, double val);
t_quat			quat_mul_vector(t_quat a, t_vec b);
t_quat			quat_mul_quat(t_quat a, t_quat b);
t_quat			create_quat(t_vec rotate_vector, double rotate_angle);
double			quat_length(t_quat q);

#endif
