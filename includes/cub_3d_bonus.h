/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:17:15 by username          #+#    #+#             */
/*   Updated: 2026/04/10 20:00:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_BONUS_H
# define CUB_3D_BONUS_H

# include "utils_bonus.h"

// ============================================================================
// MAIN FUNCTIONS
// ============================================================================
int					ft_check_args(int argc, char **argv);
t_game				*ft_loading_game(char *path_map);
void				ft_check_and_correct_door_textures(t_game *game,
						t_list **list);
void				ft_build_array_textures(t_game *game);
void				ft_create_render(t_game *game);
void				ft_create_window_img(t_game *game);
void				ft_create_minimap(t_game *game);
void				ft_load_all_textures(t_game *game);
void				ft_setup_map_and_ui(t_game *game, t_file *map_file);
void				ft_init_game(t_game *game);
void				ft_finalize_world(t_game *game);
void				ft_close_game(int exit_code);
int					ft_close_game_for_mlx(t_game *game);
void				ft_loading_menu(t_game *game);
void				ft_update_menu(t_game *game);
void				ft_draw_menu_text(t_game *game);
void				ft_restart_match(t_game *game);

// ============================================================================
// CONFIGURATION FUNCTIONS
// ============================================================================
void				ft_config_mlx(t_game *game);
void				ft_config_player(t_game *game);
void				ft_set_player_spawn_rotation(t_game *game,
						char direction_char);
void				ft_init_all_players(t_game *game);
void				ft_init_player_actions(t_game *game);
void				ft_init_flamethrower_state(t_game *game);
int					ft_is_spawn_char(char c);
void				ft_set_player_spawn(t_game *game, t_vector_int pos);
int					ft_find_player_spawn(t_game *game);
void				ft_restore_spawn_if_not_found(t_game *game,
						int found_spawn);
void				ft_setup_secondary_player(t_game *game, int idx);
void				ft_init_multiplayer_players(t_game *game);

// ============================================================================
// PARSING FUNCTIONS
// ============================================================================
void				ft_parse_map(t_game *game, t_file *map_file);
void				ft_alloc_bfs_structures(t_game *game);
void				ft_parse_colors(t_game *game, t_file *map_file);
void				ft_read_textures_in_map(t_game *game, t_file *map_file);
int					ft_path_or_color(char *str);
void				ft_normalize_map_rectangular(t_game *game);
int					ft_get_map_start_index(t_file *map_file);

int					ft_start_line_map(t_file *map_file);
int					ft_end_line_map(t_file *map_file, int start_line);
int					ft_start_column_map(t_file *map_file,
						const int *h_start_end);
int					ft_end_column_map(t_file *map_file, const int *h_start_end);
void				ft_create_game_map(t_game *game, t_file *map_file,
						const int *h_start_end, const int *w_start_end);
void				ft_rotate_map_y(t_game *game);
int					ft_check_space_surrounded(char **map, int i, int j);
int					ft_row_has_content(char *row);

void				ft_check_map(t_game *game);
int					ft_check_map_closed(t_game *game);
void				ft_create_map_transitable(t_game *game);
void				ft_print_transitable_map(t_game *game);
void				ft_create_map_transitable_aux(t_game *game);
void				check_arguments_xpm(char *path);

// ============================================================================
// GAME LOOP & UPDATE FUNCTIONS
// ============================================================================
int					ft_update(void *param);
long				ft_get_time(void);
bool				is_directive_line(char *line);
bool				is_only_spaces(const char *line);

// ============================================================================
// MOVEMENT & INPUT FUNCTIONS
// ============================================================================
void				ft_controls(t_game *game, int player_index);
void				ft_forwad_back(t_game *game, double move_speed);
void				ft_right_left(t_game *game, double move_speed);
int					ft_key_press(int keycode, t_game *game);
int					ft_key_release(int keycode, t_game *game);
int					ft_mouse_move(int x, int y, t_game *game);
int					ft_handle_player_movement(t_game *game, double move_speed,
						int player_index);
int					ft_move_player_front(t_game *game,
						t_player_actions *actions, double move_speed,
						int player_index);
int					ft_move_player_back(t_game *game, t_player_actions *actions,
						double move_speed, int player_index);
int					ft_move_player_strafe(t_game *game,
						t_player_actions *actions, double move_speed,
						int player_index);
void				ft_handle_player_rotation(t_game *game, int player_index);
int					ft_handle_system_keys(int keycode, t_game *game);
void				ft_set_key_action(int keycode, t_player_actions *actions,
						t_game *game, int player_index);
void				ft_move_direction(t_game *game, double angle,
						double move_speed, int player_index);
void				ft_move_player(t_game *game, double move_x, double move_y);

// Gamepad functions
void				ft_remap_gamepads(t_game *game);
int					ft_normalize_axis_value(int raw_value);
void				ft_reset_single_gamepad(t_gamepad *gp);
int					ft_gamepad_has_input(t_gamepad *gp);
void				ft_process_button_ab(t_gamepad *gp, struct js_event event);
void				ft_process_button_event(t_game *game, t_gamepad *gp,
						struct js_event event);
void				ft_process_axis_event(t_gamepad *gp, struct js_event event);
void				ft_process_gamepad_event(t_game *game, t_gamepad *gp,
						struct js_event event);
void				ft_process_menu_buttons(t_game *game, int i);
void				ft_gamepad_menu_input_for_all(t_game *game);
int					ft_try_open_gamepad_at(t_game *game, const char *path,
						int slot);
void				ft_init_gamepad_paths(t_game *game);
void				ft_init_gamepad(t_game *game);
void				ft_free_gamepad(t_game *game);
void				ft_recount_gamepads(t_game *game);
void				ft_handle_gamepad_error(t_game *game, int slot);
void				ft_read_gamepad_events(t_game *game, int i);
void				ft_update_gamepad(t_game *game);
void				ft_set_player_movement(t_player_actions *act,
						t_gamepad *gp);
void				ft_set_player_rotation(t_player_actions *act,
						t_gamepad *gp);
void				ft_gamepad_apply_to_player(t_game *game, t_gamepad *gp,
						int player_idx);
void				ft_apply_player0_input(t_game *game);
void				ft_apply_other_players(t_game *game);
void				ft_gamepad_movement(t_game *game);
void				ft_gamepad_handle_system_buttons(t_game *game);

// ============================================================================
// AUDIO MANAGER FUNCTIONS
// ============================================================================
t_audio_manager		*init_audio_manager(char **env);
int					audio_manager_send(t_audio_manager *audio_manager,
						const char *msg);
void				audio_manager_stop(t_audio_manager *audio_manager);
int					ft_stop_audio(pid_t pid);

void				input_detect_device(t_game *game);
void				input_merge_sources(t_game *game);
void				input_reset_gamepad(t_game *game);
void				input_reset_gamepad_for_player(t_game *game,
						int player_index);
int					input_handle_menu_a(t_game *game);
int					input_handle_menu_b(t_game *game);

// ============================================================================
// RAYCAST FUNCTIONS
// ============================================================================

void				ft_raycast(t_raycast_input *input);
void				ft_calculate_raycasts(t_game *game);
void				ft_ray_iter_up(int *position_xy, int cuadrant, int iter);
void				ft_ray_iter_right(int *position_xy, int cuadrant, int iter);
void				ft_calc_distance(int cuadrant, int *tile_ray_xy,
						t_vector2 player_position, t_vector2 *distance);
void				ft_rotate_to_cuadrant(int cuadrant, double *distance_x,
						double *distance_y);
void				ft_calc_ray_position(t_raycast *ray,
						t_vector2 *player_position, double distance_x,
						double distance_y);
void				ft_ray_type(t_raycast *ray, int cuadrant, int up_right);
void				ft_raycast_max_size(double angle, t_raycast *ray,
						double max_size, int cuadrant);

// ============================================================================
// RENDER FUNCTIONS
// ============================================================================
void				ft_render_3d(t_game *game);
void				ft_draw_minimap_border(t_game *game);
void				ft_draw_minimap_background(t_game *game);
void				ft_draw_player_indicator(t_game *game);
void				ft_draw_minimap_row(t_game *game, int my);
void				ft_draw_minimap_tile(t_game *game, int mx, int my);
void				ft_draw_tile_edges(t_game *game, int mx, int my, int color);
int					ft_get_tile_color(char tile_char);
t_vector2			ft_world_corner_to_screen(t_game *game, double wx,
						double wy);
void				ft_draw_line_minimap(t_game *game, t_vector2 p1,
						t_vector2 p2, int color);
void				ft_map2d(t_game *game);
void				ft_init_clipping(t_vector_int *src_range,
						t_vector_int *dst_start, t_texture *src,
						t_vector_int start);
void				ft_clip_horizontal(t_clip_context ctx, int start_x);
t_vector_int		ft_clip_vertical(t_texture *dst, t_texture *src,
						int start_y);
void				ft_blend_pixel(unsigned int *dst_ptr,
						unsigned int src_color, int alpha, t_vector_int pos);
void				ft_process_line(t_process_line_ctx ctx, t_vector_int y);
void				ft_draw_objects(t_game *game);
void				ft_draw_minimap_doors(t_game *game);
void				draw_column(t_game *game, int x, t_raycast *ray);
void				ft_draw_player(t_game *game);
void				ft_scale_t_image_precalc(t_texture *to,
						t_texture *text_destiny, t_game *game);
void				ft_scale_t_image(t_texture *to, t_texture *text_destiny);
void				draw_background(t_game *game);
t_texture			*get_texture_for_wall(t_game *game, t_raycast *ray);
t_texture			*get_texture_for_ceiling(t_game *game, t_vector2 *pos);
t_texture			*get_texture_for_floor(t_game *game, t_vector2 *pos);
unsigned int		get_fc_color(t_texture *texture, t_vector2 *pos);
int					ft_calculate_wall_height(t_raycast *ray, int x,
						t_game *game);
int					ft_calc_texture_x(t_raycast *ray, t_texture *texture);
t_vector2			ft_reposition_vector2(t_game *game, t_vector2 vec);
void				draw_ceiling_and_floor(t_game *game, int x, int wall_start);

void				ft_draw_line_in_image(t_game *game, t_vector2 start,
						t_vector2 end, int color);
void				ft_draw_pixel_in_img(t_img *img, int x, int y, int color);
void				ft_draw_circle(t_game *game, int cx, int cy, int color);
void				ft_draw_sq(t_game *game, int x, int y, int color);
void				ft_draw_grid_horizontal(t_game *game, int color);
void				ft_draw_grid_vertical(t_game *game, int color);
void				ft_draw_image_rgba(t_texture *dst, t_texture *src,
						int start_x, int start_y);

// Utility functions
double				ft_double_diff(double a, double b);
double				ft_vector_distance(t_vector2 a, t_vector2 b);
double				ft_normalize_angle(double angle);
double				ft_normalize_relative_angle(double angle);

// ============================================================================
// MATH FUNCTIONS
// ============================================================================
double				ft_angle_rad(double degrees);
double				ft_cos(double angle);
double				ft_sin(double angle);
double				ft_sqrt(double value);
long				ft_long_diff(long a, long b);
int					ft_int_diff(int a, int b);
int					ft_int_max(int a, int b);
// ============================================================================
// VECTOR UTILS
// ============================================================================
int					ft_abs(int n);
void				ft_vector_int_abs(t_vector_int *v);
int					ft_vector_int_max(t_vector_int v);

// ============================================================================
// COLOR FUNCTIONS
// ============================================================================
void				ft_mix_color_precalc(unsigned int *color,
						unsigned int *mix_color, int percent, t_game *game);
void				ft_mix_color(unsigned int *color, unsigned int *mix_color,
						int percent);
unsigned int		ft_parse_color_rgb(char *color_str);
int					ft_path_or_color(char *str);
int					ft_str_isnumber(char *str);

// ============================================================================
// TIMER FUNCTIONS
// ============================================================================
int					append_two_digits(char *buf, int len, int value);
void				get_timer_string(char *str, int remaining);
t_vector_int		ft_get_timer_hud_pos(t_vector_int offset,
						t_vector_int viewport, int scale, int text_width);
int					get_duration(t_game *game);
void				ft_init_timer(t_game *game);
int					ft_get_remaining(t_game *game);
void				ft_check_timer(t_game *game);
void				ft_change_duration(void *game_ptr, int direction);
void				ft_render_timer_hud(t_game *game);
void				ft_render_timer_hud_viewport(t_game *game,
						t_texture *target, t_vector_int offset,
						t_vector_int viewport);

// ============================================================================
// DOOR FUNCTIONS
// ============================================================================
void				ft_init_doors(t_game *game);
void				ft_update_doors(t_game *game);
void				ft_free_doors(t_game *game);
int					ft_is_wall_or_closed_door(t_game *game, int x, int y);
int					ft_try_toggle_door(t_game *game);

// ============================================================================
// ALIEN FUNCTIONS
// ============================================================================
void				ft_config_alien(t_game *game);
void				ft_respawn_alien(t_game *game);
void				ft_set_alien_pos(t_game *game, t_vector2 pos);
void				ft_get_exclusion_bounds(t_game *game, t_vector2 center,
						int radius, int bounds[4]);
void				ft_mark_exclusion_area(t_game *game, t_vector2 center,
						int radius);
void				ft_mark_player_areas(t_game *game);
int					ft_aviable_positions(t_game *game);
int					ft_try_set_random_position(t_vector2 *pos, int count,
						int index, t_vector_int tile);
int					ft_get_random_position(t_game *game, int indez,
						t_vector2 *pos);
void				ft_copy_transitable_map(t_game *game);
int					ft_find_respawn_candidates(t_game *game);
void				ft_update_aliens(t_game *game);
void				ft_search_heatmap(t_game *game);

// ALIEN AI
int					ft_is_blocking_tile(t_game *game, int x, int y);
int					ft_is_player_visible(t_game *game, t_player *alien,
						t_player *target, double distance);
void				ft_chase_player(t_game *game, t_player *alien);
int					ft_find_hottest_reachable_tile(t_game *game,
						t_player *alien, t_vector_int *pos);
int					ft_patrol_prepare_step(t_player *alien, t_vector2 *target,
						t_vector2 *direction, double *dist);
void				ft_patrol_apply_step(t_game *game, t_player *alien,
						t_vector2 *direction);
void				ft_move_along_path(t_game *game, t_player *alien);
void				ft_patrol_update_retry_timer(double *retry_timer,
						t_vector_int *last_goal, t_player *alien);
void				ft_patrol_search_path(t_game *game, t_player *alien,
						t_vector_int goal, t_vector_int *last_goal);
int					ft_patrol_set_goal_from_player(t_player *alien,
						t_player *player, t_vector_int *goal);
int					ft_patrol_find_near_player_goal(t_game *game,
						t_player *alien, t_vector_int *goal);
void				ft_patrol_find_and_search_goal(t_game *game,
						t_player *alien, t_vector_int *last_goal);
void				ft_patrol_move_and_cleanup(t_game *game, t_player *alien,
						t_vector_int *last_goal);

int					ft_bfs_path(t_game *game, t_bfs_request request,
						t_bfs_result result);
void				ft_bfs_init(t_bfs *bfs, t_vector_int start, int width,
						int height);
double				ft_calculate_ray_distance(double fov_y, int i,
						int render_height);
int					ft_bfs_is_valid_tile(t_game *game, t_bfs *bfs,
						t_vector_int next);
int					ft_bfs_process_neighbor(t_bfs *bfs, t_vector_int current,
						t_vector_int next);
void				ft_init_directions(int *dx, int *dy);
void				ft_button_position_size(t_button *button, t_vector_int pos,
						t_vector_int size);
void				ft_setup_settings_button(t_game *game, int idx,
						t_vector_int pos, t_settings_btn_cfg *cfg);
void				ft_alien_patrol_update(t_game *game, t_player *alien);
void				ft_check_alien_collision(t_game *game);
void				ft_kill_player(t_player *player);
int					ft_check_game_end(t_game *game);
void				ft_get_door_position(t_raycast *ray,
						t_vector_int *door_pos);
void				ft_update_render_distances(t_game *game);
void				ft_render_all_sprites(t_game *game);
void				ft_render_player_sprite(t_game *game, t_player *player);
int					ft_compare_by_distance(const void *a, const void *b);
void				ft_get_sorted_players(t_game *game);
int					ft_get_original_index(t_game *game,
						t_player *sorted_player);
int					ft_projected_x_to_screen_col(double projected_x, int width);
int					ft_project_sprite_column(t_game *game, double dx, double dy,
						t_objet_draw *draw);
void				ft_mask_alien_by_depth(t_game *game, t_texture *scaled,
						int screen_x, double alien_distance);
int					ft_compute_sprite_size(t_game *game, double base_size,
						double distance);
void				ft_loading_menu_buttons(t_game *game);
void				ft_load_menu_logo(t_game *game);
void				ft_loading_menu_frames(t_game *game);
void				ft_exit_button(void *game_ptr);
void				ft_settings_button(void *game_ptr);
void				ft_start_button(void *game_ptr);
void				ft_draw_menu_background(t_game *game);
void				ft_draw_buttons_menu(t_menu *menu);
void				ft_copy_pixel_scaled(unsigned int *dst_ptr,
						unsigned int color, int *px, int scale);
void				ft_font_process_line(t_font_ctx *ctx, t_vector_int *pos,
						int src_y);
int					ft_check_char_bounds(t_hud_draw *draw);
void				ft_menu_button(void *game_ptr);

// ============================================================================
// DEBUG FUNCTIONS
// ============================================================================
void				ft_debug_game(t_game *game);
void				ft_print_map(char **map, int error_x, int error_y);
void				debug_print_textures(t_game *game);
long				ft_long_diff(long a, long b);

unsigned char		***ft_precalc_mixcolor(void);
int					*ft_scale_precalc_x(t_game *game);
int					*ft_scale_precalc_y(t_game *game);
t_rotated_square	*ft_precalc_rotated_squares(void);

void				ft_mouse_capture(t_game *game);
void				ft_mouse_free(t_game *game);
int					ft_mouse_move(int x, int y, t_game *game);
int					ft_mouse_menu_move(int x, int y, t_game *game);
void				ft_mouse_apply_rotation(t_game *game, int delta_x);

double				ft_format_cos(double value);
double				ft_format_sin(double value);
int					ft_stop_audio(pid_t pid);
pid_t				ft_play_audio(const char *filename, char **env);

void				ft_prec_fish_eye_correction(t_game *game);
void				ft_draw_image_rgba(t_texture *dst, t_texture *src,
						int start_x, int start_y);
void				ft_mix_rgba(unsigned int *color, unsigned int *mix_color,
						int percent);
void				ft_prec_vector_cloud(t_game *game);

void				ft_init_resolutions(t_game *game);
void				ft_next_resolution(void *game_ptr);
void				ft_previous_resolution(void *game_ptr);
void				ft_loading_render(t_game *game, int render_height,
						int render_width);

void				ft_scale_t_image_precalc_two(t_texture *to,
						t_texture *text_destiny, t_game *game, int player);
void				ft_scale_t_image_precalc_three(t_texture *to,
						t_texture *text_destiny, t_game *game, int player);
void				ft_hober_buttons(t_game *game, t_menu *menu);
t_texture			*ft_loading_texture(void *mlx_ptr, char *path);
t_texture			*ft_new_texture(void *mlx_ptr, int width, int height);
int					ft_mouse_click(int button, int x, int y, t_game *game);
void				input_reset_actions(t_game *game, int player_index);

void				ft_loading_menu_settings(t_game *game);
void				ft_loading_settings_buttons(t_game *game);
void				ft_fill_settings_callbacks(void (*callbacks[9])(void *));
void				ft_fill_settings_positions(t_vector_int positions[9]);
void				ft_loading_texture_buttons(t_game *game, t_button *button,
						char *base_texture, char *hover_texture);


// ============================================================================
// MLX HD_ALLOC FUNCTIONS
// ============================================================================
void				*ft_create_window(void *mlx, int size_x, int size_y,
						char *title);
void				*ft_create_image(void *mlx, int size_x, int size_y);
void				*ft_mlx_xpm_file_to_image(void *mlx, char *filename,
						int *width, int *height);
void				hd_alloc_free_t_file(void *ptr);
void				ft_hd_alloc_mlx_destroy(void *ptr);
void				ft_hd_alloc_free_split(void *ptr);
void				ft_hd_alloc_closedir(void *ptr);

void				ft_draw_string_hud(t_texture *dst, t_texture *font,
						const char *str, t_string_ctx *ctx);
void				ft_scaled_state_init(t_scaled_state *state, t_texture *src,
						t_scaled_draw draw);
void				ft_scaled_state_clip(t_scaled_state *state, t_texture *src,
						t_vector_int dst_size);
void				ft_draw_scaled_basic(t_texture *dst, t_texture *src,
						t_scaled_state *state);
void				ft_draw_scaled_basic_row(t_texture *dst, t_texture *src,
						t_scaled_state *state, t_vector_int row);
void				ft_draw_scaled_mist(t_game *game, t_texture *src,
						t_scaled_state *state, double distance);
void				ft_draw_scaled_mist_row(t_game *game, t_texture *src,
						t_scaled_state *state, t_scaled_draw row_draw);
void				ft_scaled_mist_scan_init(t_scaled_scan *scan,
						t_texture *src, t_scaled_state *state,
						t_scaled_draw row_draw);
void				ft_scaled_mist_scan_draw(t_scaled_scan *scan, t_game *game,
						t_texture *src, t_scaled_state *state);
void				ft_draw_image_rgba_scaled(t_texture *dst, t_texture *src,
						t_scaled_draw draw);
void				ft_draw_image_rgba_scaled_plus(t_game *game, t_texture *src,
						t_scaled_draw draw);

// ============================================================================
// FLAMETHROWER FUNCTIONS
// ============================================================================
void				flamethrower(t_game *game, int player_index);
void				ft_update_flamethrower_cooldown(t_player_actions *actions,
						double delta_time);
void				ft_render_flamethrower(t_game *game, int player_index);
void				ft_render_flamethrower_hud(t_game *game, int player_index);
void				ft_flamethrower_hud(t_game *game, int player_index,
						t_texture *target, t_vector_int pos_offset);

// ============================================================================
// PRERENDER MODELS
// ============================================================================
void				ft_loading_prerender_models(t_game *game);
t_prerender_model	*ft_init_prerender_model(t_game *game, int n_frames,
						int n_angles, char *path);
void				ft_loading_textures_with_path(t_game *game,
						t_prerender_model *pre, char *path_dir);
void				ft_ordered_textures(t_prerender_model *pre);
char				*ft_get_next_file(DIR *dir, char *path_dir);
void				ft_load_prerender_texture(t_game *game,
						t_prerender_model *pre, t_prerender_load load_ctx);
void				ft_sort_textures_bubble(t_prerender_model *pre);
void				ft_print_sorted_textures(t_prerender_model *pre);

// ============================================================================
// FLAMETHROWER FUNCTIONS
// ============================================================================
void				flamethrower(t_game *game, int player_index);
void				ft_update_flamethrower_cooldown(t_player_actions *actions,
						double delta_time);
void				ft_render_flamethrower_hud(t_game *game, int player_index);

void				ft_init_durations(t_game *game);
void				ft_debug_print_map(t_game *game);
void				ft_debug_print_visited(t_game *game, int visited[128][64]);
void				ft_menu_button(void *game_ptr);

// ============================================================================
// MENU BUTTON FUNCTIONS
// ============================================================================
void				ft_decrease_players(void *game_ptr);
void				ft_increase_players(void *game_ptr);
void				ft_decrease_charges(void *game_ptr);
void				ft_increase_charges(void *game_ptr);
void				ft_decrease_timer(void *game_ptr);
void				ft_increase_timer(void *game_ptr);

void				ft_update_heatmap(t_game *game);
void				ft_create_null_texture(t_game *game);
void				ft_draw_win_screen(t_game *game);
void				ft_draw_game_over_screen(t_game *game);
int					ft_calc_delta_time(t_game *game);
void				ft_one_player(t_game *game);
void				ft_two_players(t_game *game);
void				ft_three_players(t_game *game);
void				ft_raycast_init(double *angle, int *cuadrant,
						int *tile_ray_xy, t_vector2 origin_position);
void				ft_raycast_max_size(double angle, t_raycast *ray,
						double max_size, int cuadrant);

void				ft_ray_type_door(t_raycast *ray, int cuadrant,
						int up_right);
void				ft_ray_type(t_raycast *ray, int cuadrant, int up_right);
void				ft_raycast_set_max_size(t_game *game, t_raycast *ray,
						t_raycast_ctx *ctx);
void				ft_update_player_frame(t_game *game);
#endif
