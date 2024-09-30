/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:40:13 by joamiran          #+#    #+#             */
/*   Updated: 2024/09/30 20:55:16 by joamiran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef FDF_H
# define FDF_H

# include "lib_ft/get_next_line.h"
# include "lib_ft/libft.h"
# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdarg.h>

# define PI 3.14159265358979323846

# define HEX_BASE "0123456789ABCDEF"

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define C 99
# define R 114
# define Q 113
# define E 101
# define Z 122
# define F 102
# define H 104
# define P 112
# define T 116
# define I 105
# define G 103
# define O 111
# define N 110

# define SPACE 32

# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define PLUS 65451
# define MINUS 65453
# define WHELL_UP 4
# define WHELL_DOWN 5

# define SCALE_FACTOR_Z 0
# define SCALE_FACTOR_IN 1.1f
# define SCALE_FACTOR_OUT 0.90f

// define colors
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define CYAN 0x00FFFF
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define DARK_GRAY 0x808080
# define LIGHT_GRAY 0xC0C0C0
# define MEDIUM_GRAY 0xA9A9A9

# define STD_COLOR WHITE
# define MAX_COLOR RED
# define MIN_COLOR BLUE

# define BACKGROUND 0x000000

# define MOVE_FACTOR 50

# define DEGREE_MAX 360
# define SCALE_TRIG 1000
# define ANGLE_VALUE 5

#define ISO_TILT 2

# define F_L 1000000

# define WINDOW_H 800
# define WINDOW_W 800


typedef struct window_data w_data;


typedef struct image_data
{
    void    *img;
    void    *address;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}               img_data;


typedef struct s_grid
{
    int rows;
    int cols;

    int half_x;
    int half_y;

    int max_x;
    int max_y;
    int min_x;
    int min_y;

    int width;
    int height;

}   t_grid;


typedef struct s_p
{
    int x;
    int y;
    int z;
    int color;

}   t_point;

typedef struct s_fp
{
    float x;
    float y;
    float z;
    int color;

}   f_point;

typedef struct s_use
{
    int x0;
    int y0;
    int z0;
    int dx;
    int dy;
    int dz;
    int err;
    int e2;
}   t_bres;


typedef struct lookup_table
{
    float *sin_table;
    float *cos_table;
}   t_lookup;


typedef struct window_data
{
	// mlx variables
    void    *mlx;
    void    *win;

// window variables
    int     window_w;
    int     window_h;
    char    *title;
    char    *file;

// lookup table for sin and cos
    t_lookup *lookup;

// grid variables
    int mid_x;
    int mid_y;

// image variables
    img_data img;
    float scale;
	float scale_zoom;
    float scale_z;
    int min_z;
    int max_z;

	// rotation variables

    int angle;

    int angle_x;
	int angle_y;
	int angle_z;

	float spr;

	// color variables
    int has_color;
    int color_mode;

	// info variables
    char **z_values;

	// globe radius
	float radius;

	// point variables
    t_point **p;
	f_point **i_p;
	f_point **p_b;
	f_point **p_restore;
    t_grid  *grid;

    // mode variables
	char mode;
	char interaction;

    // iterators
    int i;
    int j;

}               w_data;

// data functions
void free_data(w_data *data);
void free_pointers(void *ptr, ...);

void free_all_p(w_data *data);
void free_p(t_point **p);
void free_fp(f_point **p);

// keybind functions
int close_window(w_data *data);


int key_handle(int key, w_data *data);
int key_handle_mode(int key, w_data *data);

// mlx functions
void *init_mlx(void);
void create_window(w_data *data);
void create_image(w_data *data);

void my_mlx_pixel_put(w_data *data, int x, int y, int color);


// read functions
bool format_checker(const char *file);
char **info_parser(int fd, w_data *data);
int ft_getcolor(const char *str);
void read_fdf(w_data *data);
void assign_info(w_data *data);

void check_color(const char *line, w_data *data);
void color_mode(w_data *data);

void colorize_grayscale(w_data *data);

// draw functions

void build_model(w_data *data);

void make_image(w_data *data);

void recreate_model(w_data *data);

void draw_gui(w_data *data);

void draw_line(w_data *data, t_point *p0, t_point *p1);
void draw_poly(w_data *data);

void cycle_color_mode(int key, w_data *data);
void pcoords_conic(w_data *data);
// point arithmetics

void find_min_max_z(w_data *data);
int pointcalc (w_data *data);
t_point *center_point(w_data *data);
void center_p(w_data *data);

void zoom(int key, w_data *data);

void restore_origin(w_data *data);

// point scaling
void scale_grid(w_data *data);

void z_assign_backup(w_data *data);

// adding z to y to make the grid 3D
void z_assign(w_data *data);

void center_grid(w_data *data);

void pcoords_iso(w_data *data);

//adjusting the grid to the window
void calc_boundaries(w_data *data);
void calc_sc_mid(w_data *data);
void scale_center(w_data *data);

// moving and rotating the grid functions
void init_move(w_data *data);

void reset_movement(w_data *data);

void reset_position(w_data *data);

void move(int key, w_data *data);

void scale_z (int key, w_data *data);

void clear_image(w_data *data);

void update_img(w_data *data);

t_point **new_p(w_data *data);

void backup_data(w_data *data);

//function to colorize p
void colorize(w_data *data);
void colorize_gradient(w_data *data);

t_point **make_p(w_data *data);
f_point **backup_p(w_data *data);



// math aux functions
int ft_abs(int n);
int ft_max(int a, int b);
int ft_min(int a, int b);
int round_n(float n);
int ft_atoi_base(const char *str, const char *base_str);
float degree_to_radian(int angle);
float ft_fabs(float n);


// lookup table functions
void trig_table_sin(w_data *data);
void trig_table_cos(w_data *data);
int lookup_sin(w_data *data, int angle);
int lookup_cos(w_data *data, int angle);
void init_lookup(w_data *data);

void free_lookup(w_data *data);

// rotation functions
void rotate_x(w_data *data);
void rotate_x_key(int key, w_data *data);

void rotate_y(w_data *data);
void rotate_y_key(int key, w_data *data);

void rotate_z(w_data *data);
void rotate_z_key(int key, w_data *data);

void init_grid(w_data *data);
void init_angle(w_data *data);
void init_data_w(w_data *data);


/*
// point functions
point *create_point(int x, int y, int z);
void add_point(point **head, point *new);
void free_p(point **head);
*/

void change_interaction(int key, w_data *data);
void change_mode(int key, w_data *data);
void pan(int key, w_data *data);
void rotate(int key, w_data *data);
void zoom_in_out(int key, w_data *data);
void reset(w_data *data);
void height(int key, w_data *data);
void color(int key, w_data *data);
void display_help(int key, w_data *data);
void intro_screen(w_data *data);


void z_assign_r(w_data *data);

void show_help(w_data *data);


void pcoords_conic(w_data *data);
void build_conic(w_data *data);

void change_aero(int key, w_data *data);
void fly_conic(int key, w_data *data);
void change_focus(int key, w_data *data);
void change_focal_d(int key, w_data *data);


void pcoords_spherical(w_data *data);
void build_sphere(w_data *data);

void ro_sphere(int key, w_data *data);
void orbit(w_data *data);
void change_tilt(w_data *data);

void project_to_2d(w_data *data);

void transform_p(w_data *data);

void normalize_z_log(w_data *data);

float normalize_z(float z, w_data *data);

int key_handle_interact(int key, w_data *data);

void handle_interaction(int key, w_data *data);
void interaction_functions(int key, w_data *data);

void draw_poly_spherical(w_data *data);


void change_backup(w_data *data);

void apply_zoom(w_data *data);

#endif
