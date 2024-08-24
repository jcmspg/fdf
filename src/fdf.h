/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:19:20 by joamiran          #+#    #+#             */
/*   Updated: 2024/08/24 19:21:54 by joamiran         ###   ########.fr       */
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

# define PI 3.14159265358979323846

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define PLUS 65451
# define MINUS 65453
# define WHELL_UP 4
# define WHELL_DOWN 5

# define SCALE_FACTOR_Z 1.5
# define SCALE_FACTOR 1.5



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

}   t_grid;


typedef struct s_points
{
    int x;
    int y;
    int z;
    int color;

}   t_point;


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

typedef struct window_data
{
    void    *mlx;
    void    *win;

    int     window_width;
    int     window_height;
    char    *title;

    img_data img;
    int scale;
    int scale_z;
    int min_z;
    int max_z;
    char **z_values;
    t_point **points;
    t_grid  *grid;


}               w_data;

// data functions
void free_data(w_data *data);

// keybind functions
int close_window(w_data *data);

int key_handle(int key, w_data *data);

// mlx functions
void *init_mlx(void);
void create_window(w_data *data);
void create_image(w_data *data);

// read functions
bool format_checker(const char *file);
char **info_parser(int fd, w_data *data);
int ft_getcolor(const char *str);
void read_fdf(const char *file, w_data *data);
void assign_info(w_data *data);



// draw functions
void draw_line(w_data *data, t_point *p0, t_point *p1);
void draw_poly(w_data *data);

// point arithmetics

int pointcalc (w_data *data);
t_point *center_point(w_data *data);

// point scaling
void scale_grid(w_data *data);



// adding z to y to make the grid 3D
void z_assign(w_data *data);

void center_grid(w_data *data);

void pcoords_iso(w_data *data);

//function to colorize points
void colorize(w_data *data);

t_point **make_points(w_data *data);

// math aux functions
int ft_abs(int n);
int ft_max(int a, int b);
int ft_min(int a, int b);
int round_n(float n);
int ft_atoi_base(const char *str, int base);



/*
// point functions
point *create_point(int x, int y, int z);
void add_point(point **head, point *new);
void free_points(point **head);
*/


#endif
