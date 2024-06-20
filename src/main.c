#include "fdf.h"

int main(int argc, char ** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <width> <height>\n", argv[0]);
        return 1;
    }
    
    char *file = argv[1];
    int **points = (int **)malloc(sizeof(int *) * 2);
    int *p1;
    int *p2;

    points[0] = (int *)malloc(sizeof(int) * 2);
    points[1] = (int *)malloc(sizeof(int) * 2);

    points[0][0] = 100;
    points[0][1] = 100;

    points[1][0] = 300;
    points[1][1] = 300;

    p1 = points[0];
    p2 = points[1];



    t_grid *grid = (t_grid *)malloc(sizeof(t_grid));
    grid->rows = 0;
    grid->cols = 0;

    read_fdf(file, grid);
    printf("Rows: %d\nCols: %d\n", grid->rows, grid->cols);

    free(grid);

    w_data window;
    window.title = "FDF";
    window.window_width = 800; //ft_atoi(argv[1]);
    window.window_height = 800; //ft_atoi(argv[2]);

       


    window.mlx = init_mlx();
//  printf("Mlx address: %p\n", window.mlx);
    
    create_window(&window); 
//  printf("Window address: %p\n", window.win);

    create_image(&window);
//  printf("Image address: %p\n", window.img.address);

    

    draw_line(&window, p1, p2, 0x00FFFFFF);


    mlx_put_image_to_window(window.mlx, window.win, window.img.img, 0, 0);
   
    mlx_string_put(window.mlx, window.win, 600, 600, 0x00FFFFFF, "window size:");
    mlx_string_put(window.mlx, window.win, 600, 620, 0x00FFFFFF, ft_itoa(window.window_width));
    mlx_string_put(window.mlx, window.win, 600, 640, 0x00FFFFFF, ft_itoa(window.window_height));

    mlx_string_put(window.mlx, window.win, points[0][0], points[0][1], 0x00FFFFFF, "Point 1");
    mlx_string_put(window.mlx, window.win, points[1][0], points[1][1], 0x00FFFFFF, "Point 2");

        
    mlx_key_hook(window.win, key_handle, &window);
    
    mlx_hook(window.win, 17, 0, close_window, &window);

    mlx_loop(window.mlx);
    
    

    return 0;
}
