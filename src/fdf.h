/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:40:13 by joamiran          #+#    #+#             */
/*   Updated: 2024/10/02 23:01:33 by joamiran         ###   ########.fr       */
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
# include <errno.h>

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
# define RIGHT 65363
# define LEFT 65361
# define PLUS 65451
# define MINUS 65453
# define WHELL_UP 4
# define WHELL_DOWN 5

# define SCALE_FACTOR_IN 1.1f
# define SCALE_FACTOR_Z 0
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

# define ISO_TILT 2

# define F_L 1000000

# define WINDOW_H 800
# define WINDOW_W 800

typedef struct s_center
{
	float	x;
	float	y;
}	t_center;

typedef struct s_rotation_data
{
	float	cos_angle;
	float	sin_angle;
	int		center_y;
}	t_rotation_data;

typedef struct s_rotation_y_data
{
	float	cos_angle;
	float	sin_angle;
	int		center_x;
}	t_rotation_y_data;

typedef struct s_rotation_z_data
{
	float	cos_angle;
	float	sin_angle;
	int		center_x;
	int		center_y;
}	t_rotation_z_data;

typedef struct image_data
{
	void	*img;
	void	*address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_data;

typedef struct s_grid
{
	int	rows;
	int	cols;
	int	half_x;
	int	half_y;
	int	max_x;
	int	max_y;
	int	min_x;
	int	min_y;
	int	width;
	int	height;
}	t_grid;

typedef struct s_p
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_fp
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_f_point;

typedef struct s_use
{
	int	x0;
	int	y0;
	int	z0;
	int	dx;
	int	dy;
	int	dz;
	int	err;
	int	e2;
}	t_bres;

typedef struct lookup_table
{
	float	*sin_table;
	float	*cos_table;
}	t_lookup;

typedef struct window_data
{
	// lookup table for sin and cos
	t_lookup	*lookup;

	// mlx variables
	void		*mlx;
	void		*win;
	t_img_data	img;

	// gui text variables
	int			text_color;

	// point variables
	t_point		**p;
	t_f_point	**i_p;
	t_f_point	**p_b;
	t_f_point	**p_restore;
	t_grid		*grid;

	// window variables
	int			window_w;
	int			window_h;
	char		*title;
	char		*file;

	// grid variables
	int			mid_x;
	int			mid_y;

	// image variables
	float		scale;
	float		scale_zoom;
	float		scale_z;
	int			min_z;
	int			max_z;

	// rotation variables
	int			angle;
	int			angle_x;
	int			angle_y;
	int			angle_z;
	float		spr;

	// color variables
	int			has_color;
	int			color_mode;

	// info variables
	char		**z_values;

	// globe radius
	float		radius;

	// mode variables
	char		mode;
	char		interaction;

	// iterators
	int			i;
	int			j;

	float		extra_x;
	float		extra_y;
	float		extra_z;

}	t_w_data;

// data functions
void		free_data(t_w_data *data);
void		free_pointers(void *ptr, ...);
void		free_all_p(t_w_data *data);
void		free_p(t_point **p);
void		free_fp(t_f_point **p);

// keybind functions
int			close_window(t_w_data *data);
int			key_handle(int key, t_w_data *data);
int			key_handle_mode(int key, t_w_data *data);

// mlx functions
void		*init_mlx(void);
void		create_window(t_w_data *data);
void		create_image(t_w_data *data);
void		my_mlx_pixel_put(t_w_data *data, int x, int y, int color);

// read functions
bool		format_checker(const char *file);
char		**info_parser(int fd, t_w_data *data);
int			ft_getcolor(const char *str);
void		read_fdf(t_w_data *data);
void		assign_info(t_w_data *data);
void		check_color(const char *line, t_w_data *data);
void		color_mode(t_w_data *data);
void		colorize_grayscale(t_w_data *data);

// draw functions
void		build_model(t_w_data *data);
void		make_image(t_w_data *data);
void		recreate_model(t_w_data *data);
void		draw_gui(t_w_data *data);
void		draw_line(t_w_data *data, t_point *p0, t_point *p1);
void		draw_poly(t_w_data *data);
void		cycle_color_mode(int key, t_w_data *data);
void		pcoords_conic(t_w_data *data);

// point arithmetics
t_point		*center_point(t_w_data *data);
void		find_min_max_z(t_w_data *data);
int			pointcalc(t_w_data *data);
void		center_p(t_w_data *data);

void		restore_origin(t_w_data *data);

// point scaling
void		zoom(int key, t_w_data *data);
void		center_grid(t_w_data *data);

// point coordinates
void		pcoords_iso(t_w_data *data);

// adjusting the grid to the window
void		calc_boundaries(t_w_data *data);
void		calc_sc_mid(t_w_data *data);
void		scale_center(t_w_data *data);

// moving and rotating the grid functions
void		pan(int key, t_w_data *data);
void		reset_position(t_w_data *data);
void		move(int key, t_w_data *data);

void		scale_z(int key, t_w_data *data);

void		clear_image(t_w_data *data);

void		update_img(t_w_data *data);

t_point		**new_p(t_w_data *data);

void		backup_data(t_w_data *data);

// function to colorize p
void		colorize(t_w_data *data);

t_point		**make_p(t_w_data *data);
t_f_point	**backup_p(t_w_data *data);

// math aux functions
int			ft_abs(int n);
int			ft_max(int a, int b);
int			ft_min(int a, int b);
int			round_n(float n);
int			ft_atoi_base(const char *str, const char *base_str);
float		degree_to_radian(int angle);
float		ft_fabs(float n);

// lookup table functions
void		trig_table_sin(t_w_data *data);
void		trig_table_cos(t_w_data *data);
int			lookup_sin(t_w_data *data, int angle);
int			lookup_cos(t_w_data *data, int angle);
void		init_lookup(t_w_data *data);

void		free_lookup(t_w_data *data);

// rotation functions
void		rotate_x(t_w_data *data);
void		rotate_x_key(int key, t_w_data *data);

void		rotate_y(t_w_data *data);
void		rotate_y_key(int key, t_w_data *data);

void		rotate_z(t_w_data *data);
void		rotate_z_key(int key, t_w_data *data);

void		init_grid(t_w_data *data);
void		init_angle(t_w_data *data);
void		init_data_w(t_w_data *data);

void		change_mode(int key, t_w_data *data);
void		pan(int key, t_w_data *data);
void		rotate(int key, t_w_data *data);
void		zoom_in_out(int key, t_w_data *data);
void		reset(t_w_data *data);
void		color(int key, t_w_data *data);
void		display_help(int key, t_w_data *data);
void		intro_screen(t_w_data *data);

void		show_help(t_w_data *data);
void		show_help2(t_w_data *data, int pos);
void		show_help3(t_w_data *data, int author_x, int author_y, int pos);

void		pcoords_conic(t_w_data *data);
void		build_conic(t_w_data *data);

void		change_aero(int key, t_w_data *data);
void		fly_conic(int key, t_w_data *data);
void		change_focus(int key, t_w_data *data);
void		change_focal_d(int key, t_w_data *data);

void		pcoords_spherical(t_w_data *data);
void		build_sphere(t_w_data *data);

void		ro_sphere(int key, t_w_data *data);
void		orbit(t_w_data *data);
void		change_tilt(t_w_data *data);

void		transform_p(t_w_data *data);

void		normalize_z_log(t_w_data *data);

float		normalize_z(float z, t_w_data *data);

void		handle_interaction(int key, t_w_data *data);
void		interaction_functions(int key, t_w_data *data);

void		draw_poly_spherical(t_w_data *data);

void		change_backup(t_w_data *data);

void		apply_zoom(t_w_data *data);

int			increment(int start, int end);
void		bresen_calc(t_point *p0, t_point *p1, t_bres *bresen);

void		draw_horizontal(t_w_data *data);
void		draw_vertical(t_w_data *data);

int			calculate_color(int z, int min_z, int max_z);
int			get_negative_color(int z, int min_z);
int			get_positive_color(int z, int max_z);
int			get_zero_color(void);
void		colorize_gradient(t_w_data *data);

void		set_origin(t_w_data *data);

void		initialize_boundaries(t_w_data *data);
void		update_boundaries(t_w_data *data);
void		calc_boundaries(t_w_data *data);

void		put_string_with_offset(t_w_data *data, int x, int y, char *string);
void		draw_static_text(t_w_data *data, int x_left, int y,
				int line_spacing);
void		draw_dynamic_value(t_w_data *data, int x_left, int y, float value);
void		draw_information(t_w_data *data);
void		draw_dynamic_values(t_w_data *data, int x_left,
				int y, int line_spacing);

void		start_iso(t_w_data *data);
void		switch_to_iso(t_w_data *data);
void		switch_to_globe(t_w_data *data);
void		switch_to_conic(t_w_data *data);

void		calculate_movement(int keycode, t_w_data *data,
				int *movement_x, int *movement_y);
void		apply_movement(t_w_data *data, int movement_x, int movement_y);

#endif
