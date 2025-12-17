/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:38:54 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/17 16:32:25 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB_3D_BONUS_H
# define CUB_3D_BONUS_H

# include "utils_bonus.h"

// ============================================================================
// MAIN FUNCTIONS
// ============================================================================
int				ft_check_args(int argc, char **argv);
t_game			*ft_loading_game(char *path_map);
void			ft_close_game(int exit_code);
int				ft_close_game_for_mlx();
void			ft_init_menu(t_game *game);
void			ft_free_menu(t_game *game);
void			ft_update_menu(t_game *game);
void			ft_draw_menu_text(t_game *game);

// ============================================================================
// CONFIGURATION FUNCTIONS
// ============================================================================
void			ft_config_mlx(t_game *game);
void			ft_config_player(t_game *game);

// ============================================================================
// PARSING FUNCTIONS
// ============================================================================
void			ft_parse_map(t_game *game, t_file *map_file);
void 			ft_parse_colors(t_game *game, t_file *map_file);
void			ft_read_textures_in_map(t_game *game, t_file *map_file);
int				ft_path_or_color(char *str);


// Map parsing utilities
int				ft_get_map_start_index(t_file *map_file);
int				ft_start_line_map(t_file *map_file);
int				ft_end_line_map(t_file *map_file, int start_line);
int				ft_start_column_map(t_file *map_file, const int *height_start_end);
int				ft_end_column_map(t_file *map_file, const int *height_start_end);
void			ft_create_game_map(t_game *game, t_file *map_file, const int *height_start_end, const int *width_start_end);
void			ft_rotate_map_y(t_game *game);

// Map validation
void			ft_check_map(t_game *game);
int				ft_check_map_closed(t_game *game);

// XPM parsing
void			check_arguments_xpm(char *path);

// ============================================================================
// GAME LOOP & UPDATE FUNCTIONS
// ============================================================================
int				ft_update(void *param);
long			ft_get_time(void);

// ============================================================================
// MOVEMENT & INPUT FUNCTIONS
// ============================================================================
void			ft_controls(t_game *game);
void 			ft_forwad_back(t_game *game, double move_speed);
void 			ft_right_left(t_game *game, double move_speed);
int 			ft_key_press(int keycode, t_game *game);
int 			ft_key_release(int keycode, t_game *game);
int				ft_mouse_move(int x, int y, t_game *game);
void			ft_move_direction(t_game *game, double angle, double move_speed);
void			ft_move_player(t_game *game, double move_x, double move_y);


// Gamepad functions
void			ft_init_gamepad(t_game *game);
void			ft_free_gamepad(t_game *game);
void			ft_update_gamepad(t_game *game);
void			ft_gamepad_movement(t_game *game);
int			audio_play(t_game *game, const char *path, pid_t *pid_out);
int			audio_stop(pid_t *pid);
int			audio_play_steps(t_game *game, const char *path);
int			audio_stop_steps(t_game *game);
int			audio_play_menu(t_game *game, const char *path);
int			audio_stop_menu(t_game *game);
void		input_detect_device(t_game *game);
void		input_merge_sources(t_game *game);
void		input_reset_gamepad(t_game *game);
int			input_handle_menu_a(t_game *game);
int			input_handle_menu_b(t_game *game);

// ============================================================================
// RAYCAST FUNCTIONS
// ============================================================================
void			ft_raycast(t_game *game, double angle, t_raycast *ray, double max_size);
void			ft_calculate_raycasts(t_game *game);
void			ft_ray_iter_up(int *position_xy, int cuadrant, int iter);
void			ft_ray_iter_right(int *position_xy, int cuadrant, int iter);
void			ft_calc_distance(int cuadrant, int *tile_ray_xy, t_vector2 player_position, t_vector2 *distance);
void			ft_rotate_to_cuadrant(int cuadrant, double *distance_x, double *distance_y);
void			ft_calc_ray_position(t_raycast *ray, t_vector2 *player_position, double distance_x, double distance_y);
void			ft_ray_type(t_raycast *ray, int cuadrant, int up_right);
void			ft_raycast_max_size(t_game *game, double angle, t_raycast *ray, double max_size, int cuadrant);

// ============================================================================
// RENDER FUNCTIONS
// ============================================================================
void			ft_render_3d(t_game *game);
void			ft_map2D(t_game *game);
void			draw_column(t_game *game, int x, t_raycast *ray);
void			ft_draw_player(t_game *game);
void			ft_scale_t_image_precalc(t_texture *tex_origin, t_texture *text_destiny, t_game *game);
void			ft_scale_t_image(t_texture *tex_origin, t_texture *text_destiny);

// Drawing utilities
void			ft_draw_line_in_image(t_game *game, t_vector2 start, t_vector2 end, int color);
void			ft_draw_pixel_in_img(t_img *img, int x, int y, int color);
void			ft_draw_circle(t_game *game, int cx, int cy, int color);
void			ft_draw_sq(t_game *game, int x, int y, int color);
void			ft_draw_grid_horizontal(t_game *game, int color);
void			ft_draw_grid_vertical(t_game *game, int color);
void			ft_draw_transparent_image(t_texture *dst, t_texture *src,
						int start_x, int start_y);

// Utility functions
double			ft_double_diff(double a, double b);
double			ft_vector_distance(t_vector2 a, t_vector2 b);
double			ft_normalize_angle(double angle);

// ============================================================================
// MATH FUNCTIONS
// ============================================================================
double			ft_angle_rad(double degrees);
double			ft_cos(double angle);
double			ft_sin(double angle);
double			ft_sqrt(double value);

// ============================================================================
// VECTOR UTILS
// ============================================================================
int				ft_abs(int n);
void			ft_vector_int_abs(t_vector_int *v);
int				ft_vector_int_max(t_vector_int v);

// ============================================================================
// COLOR FUNCTIONS
// ============================================================================
void			ft_mix_color_precalc(unsigned int *color, unsigned int  *mix_color, int percent, t_game *game);
void			ft_mix_color(unsigned int *color, unsigned int  *mix_color, int percent);
unsigned int	ft_parse_color_rgb(char *color_str);
int				ft_path_or_color(char *str);
int				ft_str_isnumber(char *str);

// ============================================================================
// DOOR FUNCTIONS
// ============================================================================
void			ft_init_doors(t_game *game);
void			ft_update_doors(t_game *game);
void			ft_check_door_triggers(t_game *game);
void			ft_animate_door(t_door *door, double delta_time);
int				ft_is_door(t_game *game, int x, int y);
t_door			*ft_get_door_at(t_game *game, int x, int y);
void			ft_free_doors(t_game *game);
double			ft_get_door_height(t_door *door);
int				ft_is_wall_or_closed_door(t_game *game, int x, int y);

// ============================================================================
// ALIEN FUNCTIONS
// ============================================================================
void			ft_init_aliens(t_game *game);
void			ft_config_aliens(t_game *game);
void			ft_update_aliens(t_game *game);
void			ft_render_aliens(t_game *game);
void			ft_free_aliens(t_game *game);
//void			ft_calculate_patrol_points(t_game *game, t_alien *alien);

// ============================================================================
// DEBUG FUNCTIONS
// ============================================================================
void			ft_debug_game(t_game *game);
void			ft_print_map(char **map, int error_x, int error_y);
void			debug_print_textures(t_game *game);
long			ft_long_diff(long a, long b);

unsigned char 	***ft_precalc_mixcolor(void);
int				*ft_scale_precalc_x(t_game *game);
int				*ft_scale_precalc_y(t_game *game);
t_rotated_square *ft_precalc_rotated_squares(void);

void			ft_toggle_mouse_capture(t_game *game);
int				ft_mouse_move(int x, int y, t_game *game);
void			ft_init_mouse(t_game *game);

double			ft_format_cos(double value); 
double			ft_format_sin(double value);
int				ft_stop_audio(pid_t pid);
pid_t			ft_play_audio(const char *filename, char **env);

void			ft_prec_fish_eye_correction(t_game *game);
void			ft_draw_transparent_image(t_texture *dst, t_texture *src,
		int start_x, int start_y);
void			ft_mix_color_alpha(unsigned int *color, unsigned int  *mix_color, int percent);
void			ft_prec_vector_cloud(t_game *game);

void			ft_init_resolutions(t_game *game);
void			ft_next_resolution(t_game *game);
void			ft_loading_render(t_game *game, int render_height, int render_width);

void			ft_scale_t_image_precalc_two(t_texture *tex_origin,
		t_texture *text_destiny, t_game *game, int player);

#endif