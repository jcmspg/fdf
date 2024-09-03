#include "fdf.h"

int main(int argc, char ** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <width> <height>\n", argv[0]);
        return 1;
    }
    
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
	window.scale = 1.0;
    window.scale_z = 1.0;

    window.file = argv[1];

	init_lookup(&window);   
	// print the sin and cos tables
/* 	int i = 0;
	while (i < DEGREE_MAX)
	{
		printf("sin[%d] = %f\n", i, window.lookup->sin_table[i]);
		printf("cos[%d] = %f\n", i, window.lookup->cos_table[i]);
		i++;
	} */

	init_angle(&window);
/* 	// print the angle_x , y and z
	printf("angle_x = %d\n", window.angle_x);
	printf("angle_y = %d\n", window.angle_y);
	printf("angle_z = %d\n", window.angle_z); */


    window.mlx = init_mlx();
//  printf("Mlx address: %p\n", window.mlx);
    if (window.mlx == NULL)
    {
        fprintf(stderr, "Failed to initialize mlx\n");
        return 1;
    }
    create_window(&window);
    create_image(&window);

    read_fdf(&window);
    //build_model(&window);
	//backup_data(&window);
	//make_image(&window);

    //intro screen
    intro_screen(&window);

	//reset_position(&window);
    //print all points.z


    // key input handling
    mlx_key_hook(window.win, key_handle, &window);
    
    // click upper X to close 
    mlx_hook(window.win, 17, 0, close_window, &window);

    mlx_loop(window.mlx);

    // Free the allocated memory

    


    return 0;
}
