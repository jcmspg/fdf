#include "fdf.h"

int main(int argc, char ** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <width> <height>\n", argv[0]);
        return 1;
    }
    
    char *file = argv[1];
    int **map;
    t_point **test_points;
    w_data window;
  
    window.title = "FDF";
    window.window_width = 800; //ft_atoi(argv[1]);
    window.window_height = 800; //ft_atoi(argv[2]);


    t_grid *grid = (t_grid *)malloc(sizeof(t_grid));
    if (grid == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    grid->rows = 0;
    grid->cols = 0;

    read_fdf(file, grid);
    printf("Rows: %d\nCols: %d\n", grid->rows, grid->cols);
    
    map = map_alloc(file, grid);
    if (map == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        free(grid);
        return 1;
    }
    
    for (int i = 0; i < grid->rows; i++)
    {
        for (int j = 0; j < grid->cols; j++)
        {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }

    test_points = make_points(grid, &window);
    

    while (1)
    {
        for (int i = 0; i < grid->rows; i++)
        {
            for (int j = 0; j < grid->cols; j++)
            {
                printf("(%d, %d) ", test_points[i][j].x, test_points[i][j].y);
            }
            printf("\n");
        }
        break;
    }


  

    
    
   



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


    
    draw_poly(&window, grid, test_points, 0x00FF0000);





    mlx_put_image_to_window(window.mlx, window.win, window.img.img, 0, 0);
   
    mlx_string_put(window.mlx, window.win, 600, 600, 0x00FFFFFF, "window size:");
    mlx_string_put(window.mlx, window.win, 600, 620, 0x00FFFFFF, ft_itoa(window.window_width));
    mlx_string_put(window.mlx, window.win, 600, 640, 0x00FFFFFF, ft_itoa(window.window_height));


        
    mlx_key_hook(window.win, key_handle, &window);
    
    mlx_hook(window.win, 17, 0, close_window, &window);

    mlx_loop(window.mlx);

    // Free the allocated memory
    for (int i = 0; i < 4; i++)
    {
        free(test_points[i]);
    }
    free(test_points);
    free(grid);
    free(map);


    return 0;
}
