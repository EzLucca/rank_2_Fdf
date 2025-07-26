/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edlucca <edlucca@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 10:40:18 by edlucca           #+#    #+#             */
/*   Updated: 2025/07/26 14:20:52 by edlucca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include "fdf_structs.h"
# include "../lib/libft/include/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# define WIDTH 1280 /* Initial window width */
# define HEIGHT 720 /* Initial window height */
# define TITLE "Fdf" /* Text shown in window title bar */
# define BACKGROUND			0x22222200
# define COLOR_TEN			0x9e0142ff
# define COLOR_NINE			0xd53e4fff
# define COLOR_EIGHT		0xf46d43ff
# define COLOR_SEVEN		0xfdae61ff
# define COLOR_SIX			0xfee08bff
# define COLOR_FIVE			0xe6f598ff
# define COLOR_FOUR			0xabdda4ff
# define COLOR_THREE		0x66c2a5ff
# define COLOR_TWO			0x3288bdff
# define COLOR_ONE			0x5e4fa2ff

/**
 * @brief Calculates the color of a point along a line based on its position
 *        between two endpoints in 2D space.
 *
 * @param current The current point whose color needs to be determined.
 * @param a The starting point of the line.
 * @param b The ending point of the line.
 * @return The computed integer color value for the `current` point.
 */
int		get_color(t_point2d current, t_point2d a, t_point2d b);

/**
 * @brief Validates a line of input to ensure it conforms to the expected format
 *        for point coordinates or values.
 *
 * @param line The input string to validate.
 * @return true if the line is valid; false otherwise.
 */
bool	points_check(char *line);

/**
 * @brief Iterates through the map grid and draws lines between each point
 *        to render the full wireframe image.
 *
 * This function casts the generic `param` pointer to a `t_fdf` structure,
 * clears the current image buffer, and then loops through each point in
 * the map using nested rows and columns. For each point, it calls `draw_line()`
 * to render connections, resulting in a complete representation of the map.
 *
 * @param param A void pointer to the `t_fdf` structure containing the map data
 *              and image buffer context.
 * @return void
 */
void	draw_image(void *param);

/**
 * @brief Handles keyboard input for toggling color mode and rotation axes
 *        in the FDF rendering project.
 *
 * This function casts the generic parameter to a `t_fdf` structure and checks
 * for key presses using the MLX42. It toggles the z-coloring mode
 * if the 'C' key is pressed, and sets rotation flags for x, y, and z axes 
 * based on keys '1', '2', and '3' respectively.
 *
 * @param param A void pointer to the `t_fdf` structure that contains rendering
 *              context, map data, and rotation state.
 * @return void
 */
void	ft_hook_project(void *param);

/**
 * @brief Handles keyboard input to control rotational angles and scaling
 *        of the map in the FDF project.
 *
 * Adjusts rotation angles (`alpha`, `beta`) and vertical scale (`zscale`) 
 * based on directional keys. The `COMMA` and `PERIOD` keys control the sign of
 * the transformation, allowing clockwise or counter-clockwise rotation or 
 * increase/decrease in scale.
 *
 * @param param A void pointer to the `t_fdf` structure containing the rendering
 *              context, input state, and transformation parameters.
 * @return void
 */
void	ft_hook_rotate(void *param);

/**
 * @brief Handles real-time keyboard input for viewport navigation,
 *        zooming, and program control within the FDF rendering context.
 *
 * Trigger corresponding actions such as resetting the map, closing the window,
 * moving the rendered image on screen via offsets, and zooming in or out.
 *
 * @param param A void pointer to the `t_fdf` structure, containing all relevant
 *              rendering and map data necessary for input handling.
 * @return void
 */
void	ft_hook(void *param);

/**
 * @brief Handles scroll wheel input to zoom the map in or out.
 *
 * This function adjusts the zoom factor of the map based on the scroll 
 * direction. Positive `ydelta` zooms in (increases scale), while negative
 * `ydelta` zooms out (decreases scale) with a safety check to prevent 
 * zooming below zero.
 *
 * @param xdelta Unused horizontal scroll delta.
 * @param ydelta Vertical scroll delta: determines zoom direction.
 * @param param A void pointer to the `t_fdf` structure containing map and zoom
 * state.
 * @return void
 */
void	ft_scroll_hook(double xdelta, double ydelta, void *param);

/**
 * @brief Handles window resize events and updates the rendering context
 * accordingly.
 *
 * This function is called whenever the display window is resized. It deletes
 * the old image buffer, creates a new one with the updated dimensions, and 
 * re-centers the map on screen by recalculating offsets based on zoom and 
 * map size.
 *
 * @param width  The new width of the window.
 * @param height The new height of the window.
 * @param param  A void pointer to the `t_fdf` structure containing rendering
 *               and map data.
 * @return void
 */
void	resize_hook(int width, int height, void *param);

/**
 * @brief Assigns a color value to each 3D point in the map based on its height.
 *
 * This function iterates through all points in the 2D grid representation of
 * the map, calculates a color gradient percentage using the point's 
 * z-coordinate (height), and assigns the corresponding color to `zcolor` using
 * the `colors()` function. The color gradient is determined by interpolating
 * between `map->low` and `map->high` elevation values via `colormix()`.
 *
 * @param map Pointer to the `t_map` structure containing grid data and 
 * elevation bounds.
 * @return void
 */
void	set_zcolor(t_map *map);

/**
 * @brief Main loop handler that processes user input, applies transformations,
 *        and triggers image rendering.
 *
 * This function is repeatedly called in the rendering loop. It checks for 
 * keyboard input (movement, rotation, projection mode) via separate hook 
 * functions, applies continuous rotation if enabled, and redraws the image 
 * with updated parameters.
 *
 * @param param A void pointer to the `t_fdf` structure containing the map,
 * input state, and rendering context.
 * @return void
 */
void	loop_handler(void *param);

/**
 * @brief Clears the image buffer by setting every pixel to the background color
 *
 * This function iterates over each pixel in the image and uses `mlx_put_pixel`
 * to assign it the `BACKGROUND` color constant, effectively resetting the image
 * canvas before drawing new content.
 *
 * @param image Pointer to the `mlx_image_t` structure representing the image 
 * buffer.
 * @return void
 */
void	reset_draw(mlx_image_t *image);

/**
 * @brief Resets all map-related rendering parameters to their default values.
 *
 * This function restores the map state by resetting transformation attributes
 * such as rotation angles (`alpha`, `beta`, `xrotate`, `yrotate`, `zrotate`),
 * scaling factors (`zoom`, `zscale`), and screen offsets. It also disables
 * z-based color shading. The map is re-centered on the window based on the
 * current size and zoom level.
 *
 * @param fdf Pointer to the `t_fdf` structure containing both MLX context and
 * map data.
 * @return void
 */
void	reset_map(t_fdf *map);

/**
 * @brief Displays the control menu overlay in the FDF window.
 *
 * This function uses MLX42's `mlx_put_string()` to draw a list of key bindings
 * and their corresponding actions directly onto the window. 
 *
 * @param mlx Pointer to the MiniLibX context used to render the text.
 * @return void
 */
void	display_menu(mlx_t *mlx);

/**
 * @brief Parses the map data from a file descriptor and populates the map grid.
 *
 * This function reads each line of input from the file using `get_next_line`,
 * trims the newline character, and passes the cleaned line to `process_points()`
 * for conversion into structured map data. It processes exactly `map->rows`
 * lines and reports a map-related error if reading fails.
 *
 * @param fd   File descriptor from which the map data is read.
 * @param map  Pointer to the `t_map` structure that will store the parsed grid.
 * @return void
 */
void	parse_map(int fd, t_map *map);

/**
 * @brief Allocates memory for the map's 2D and 3D point grids.
 *
 * This function initializes `grid3d` and `grid2d` arrays within the map,
 * allocating memory for each row and column according to `map->rows` and
 * `map->cols`.
 * If any allocation fails, it frees the allocated resources and triggers
 * a map-related error handler.
 *
 * @param map Pointer to the `t_map` structure that will store the grid data.
 * @return void
 */
void	allocate_grid(t_map *map);

/**
 * @brief Applies rotation around the X-axis to the given Y and Z coordinates.
 *
 * This function modifies the values pointed to by `y` and `z` to reflect a 
 * rotation around the X-axis by angle `alpha` (in radians). It uses standard
 * 3D rotation matrix logic:
 *
 *     y' = y * cos(alpha) + z * sin(alpha)
 *     z' = -y * sin(alpha) + z * cos(alpha)
 *
 * @param y Pointer to the Y coordinate to be rotated.
 * @param z Pointer to the Z coordinate to be rotated.
 * @param alpha Rotation angle in radians.
 * @return void
 */
void	rotate_x(double *y, double *z, double alpha);

/**
 * @brief Applies rotation around the Y-axis to the given X and Z coordinates.
 *
 * This function modifies the values pointed to by `x` and `z` to reflect a 
 * rotation around the Y-axis by angle `beta` (in radians). It uses standard
 * 3D rotation matrix logic:
 *
 *     x' = x * cos(beta) + z * sin(beta)
 *     z' = -x * sin(beta) + z * cos(beta)
 *
 * @param x Pointer to the X coordinate to be rotated.
 * @param z Pointer to the Z coordinate to be rotated.
 * @param beta Rotation angle in radians.
 * @return void
 */
void	rotate_y(double *x, double *z, double beta);

/**
 * @brief Applies rotation around the Z-axis to the given X and Y coordinates.
 *
 * This function updates the values pointed to by `x` and `y` to reflect a
 * rotation around the Z-axis by angle `gamma` (in radians). It uses the
 * standard 2D rotation matrix applied within the XY-plane:
 *
 *     x' = x * cos(gamma) - y * sin(gamma)
 *     y' = x * sin(gamma) + y * cos(gamma)
 *
 * @param x Pointer to the X coordinate to be rotated.
 * @param y Pointer to the Y coordinate to be rotated.
 * @param gamma Rotation angle in radians.
 * @return void
 */
void	rotate_z(double *x, double *y, double gamma);

/**
 * @brief Prints an error message and terminates the program.
 *
 * This function displays the provided error string prefixed with `"Error: "`
 * using a custom `ft_printf` implementation, and then exits the program 
 * immediately with failure status.
 *
 * @param str The error message to display before exiting.
 * @return void
 */
void	ft_error(char *str);

/**
 * @brief Frees all allocated memory associated with a map structure.
 *
 * This function safely deallocates memory used by the 2D and 3D point grids in
 * the `t_map` structure using `ft_free_tab()`, and then frees the map itself.
 * It includes null checks to prevent invalid free operations.
 *
 * @param map Pointer to the `t_map` structure to be deallocated.
 * @return void
 */
void	free_map(t_map *map);

/**
 * @brief Prints an error message, closes the given file descriptor, and 
 * terminates the program.
 *
 * This function is used for error handling in scenarios involving open file 
 * descriptors. It logs the error message prefixed with `"Error: "` using
 * `ft_printf`, safely closes the provided file descriptor `fd`, and exits
 * the program with a failure status.
 *
 * @param str The error message to display before exiting.
 * @param fd  The file descriptor to close before termination.
 * @return void
 */
void	ft_error_close(char *str, int fd);

/**
 * @brief Displays a map-related error message, closes a file descriptor,
 *        frees the map structure, and terminates the program.
 *
 * This function is designed for graceful failure when encountering errors
 * during map processing. It prints an error message using `ft_printf`,
 * closes the associated file descriptor, deallocates the map via `free_map`,
 * and exits the program with a failure status.
 *
 * @param str  The error message to display.
 * @param fd   The file descriptor to close.
 * @param map  Pointer to the `t_map` structure to be freed.
 * @return void
 */
void	ft_error_map(char *str, int fd, t_map *map);

/**
 * @brief Converts a character to uppercase.
 *
 * This function takes an index and a pointer to a character.
 * The index is incremented (unused), and the character pointed to by `c`
 * is converted to uppercase using `ft_toupper()`.
 *
 * @param i An unsigned integer index (unused).
 * @param c Pointer to the character to be converted.
 * @return void
 */
void	ft_upper(unsigned int i, char *c);

/**
 * @brief Opens, validates, parses, and initializes a map from a given file.
 *
 * This function performs a comprehensive series of operations to load a map:
 * Opens and performs an initial validation pass on the grid structure
 * Allocates memory for the map's grid based on the validated dimensions.
 * Parse the actual point data into the allocated grid.
 *
 * @param filename The path to the map file (e.g., ".fdf" file).
 * @return A pointer to a newly allocated and initialized `t_map` structure
 * containing the parsed map data.
 */
t_map	*open_validate_map(char *filename);

/**
 * @brief Initializes the FDF application (map, MLX windows, MLX image).
 *
 * Sets up core FDF components:
 * - Loads and validates map data from `filename`.
 * - Initializes MLX42 context.
 * - Creates a new image buffer for rendering.
 *
 * @param filename Path to the map file.
 * @param fdf Pointer to the `t_fdf` structure to initialize.
 */
void	init_fdf(char *filename, t_fdf	*fdf);

/**
 * @brief Initializes the members of a `t_map` structure to default values.
 *
 * Sets initial values for angles, offsets, zoom, scale, color usage,
 * min/max Z-values, dimensions, and grid pointers.
 *
 * @param map Pointer to the `t_map` structure to be initialized.
 */
void	init_map(t_map *map);

#endif
