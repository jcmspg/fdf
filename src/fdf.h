/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamiran <joamiran@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:19:20 by joamiran          #+#    #+#             */
/*   Updated: 2024/06/24 19:17:38 by joamiran         ###   ########.fr       */
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


typedef struct image_data
{
    void    *img;
    void    *address;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}               img_data;

typedef struct window_data
{
    void    *mlx;
    void    *win;

    int     window_width;
    int     window_height;
    char    *title;

    img_data img;

}               w_data;

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

// data functions
void free_data(w_data *win);

// keybind functions
int close_window(w_data *win);

int key_handle(int key, w_data *win);

// mlx functions
void *init_mlx(void);
void create_window(w_data *window);
void create_image(w_data *window);

// read functions
void read_fdf(const char *file, t_grid *grid);
int **map_alloc(const char *line, t_grid *grid);

// draw functions
void draw_line(w_data *window, t_point *p0, t_point *p1, int color);
void draw_poly(w_data *window, t_grid *grid, t_point **points, int color);

// point arithmetics

int pointcalc (w_data *data, t_grid *grid);
t_point *center_point(w_data *data);

void center_grid(t_grid *grid, t_point **points);


void pcoords_iso(t_point **points, t_grid *grid);

t_point **make_points(t_grid *grid, w_data *data);

// math aux functions
int ft_abs(int n);
int ft_max(int a, int b);
int ft_min(int a, int b);
int round_n(float n);



/*
// point functions
point *create_point(int x, int y, int z);
void add_point(point **head, point *new);
void free_points(point **head);
*/


#endif
