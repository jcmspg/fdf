#include "fdf.h"

int main(int argc, char ** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <width> <height>\n", argv[0]);
        return 1;
    }
    
    char *file = argv[1];
    w_data window;
  
    window.title = "FDF";
    window.window_width = 800; //ft_atoi(argv[1]);
    window.window_height = 800; //ft_atoi(argv[2]);


    window.grid = (t_grid *)malloc(sizeof(t_grid));
    if (window.grid == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    window.grid->rows = 0;
    window.grid->cols = 0;

    read_fdf(file, &window);
    printf("Rows: %d\nCols: %d\n", window.grid->rows, window.grid->cols);
    
   // window.points = make_points(&window);
    

    window.mlx = init_mlx();
//  printf("Mlx address: %p\n", window.mlx);
    if (window.mlx == NULL)
    {
        fprintf(stderr, "Failed to initialize mlx\n");
        return 1;
    }
    
    create_window(&window); 
//  printf("Window address: %p\n", window.win);

    create_image(&window);
//  printf("Image address: %p\n", window.img.address);

    
    pcoords_iso(&window);

    center_grid(&window);


    //adding z to y coords to create 3d effect
    //

    z_assign(&window);
    colorize(&window);


    draw_poly(&window);

    //print the z coord of each point
    
   /* int i = 0;
    int j = 0;

    while (i < window.grid->rows)
    {
        j = 0;
        while (j < window.grid->cols)
        {
            printf("z: %d\n", window.points[i][j].z);
            j++;
        }
        i++;
    }*/


    mlx_put_image_to_window(window.mlx, window.win, window.img.img, 0, 0);

    /*
    mlx_string_put(window.mlx, window.win, 600, 600, 0x00FFFFFF, "window size:");
    mlx_string_put(window.mlx, window.win, 600, 620, 0x00FFFFFF, ft_itoa(window.window_width));
    mlx_string_put(window.mlx, window.win, 600, 640, 0x00FFFFFF, ft_itoa(window.window_height));
    */
    
    // key input handling
    mlx_key_hook(window.win, key_handle, &window);
    
    // click upper X to close 
    mlx_hook(window.win, 17, 0, close_window, &window);

    mlx_loop(window.mlx);

    // Free the allocated memory

    


    return 0;
}
