/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 10:16:23 by smiller       #+#    #+#                 */
/*   Updated: 2020/11/11 10:52:59 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "parse.h"
# include <math.h>
# include <fcntl.h>

# define SPD .13
# define ROT_SPD .09

typedef struct		s_sprite
{
	double			x;
	double			y;
	double			dist;
	int				counter;
}					t_sprite;

typedef struct		s_texture
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	char			*tex_path;
	char			*get_color;
}					t_texture;

typedef struct		s_vars {
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				screen_width;
	int				screen_height;
	unsigned int	color;
	int				floor;
	int				ceiling;
	char			**map;
	int				map_x;
	int				map_y;
	int				map_i;
	double			camera_x;
	int				ray_x;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			cameraplane_x;
	double			cameraplane_y;
	double			raydir_x;
	double			raydir_y;
	int				reverse_raydir;
	int				mapray_x;
	int				mapray_y;
	double			deltadist_x;
	double			deltadist_y;
	double			sidedist_x;
	double			sidedist_y;
	int				cardinal_dir;
	double			perpwalldist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				draw_line;
	int				fwd;
	int				back;
	int				right;
	int				left;
	int				look_right;
	int				look_left;
	double			old_dir_x;
	double			old_dir_y;
	double			old_cameraplane_x;
	t_texture		tex[5];
	double			wall_x;
	int				t;
	t_sprite		*sprite;
	double			*z_buffer;
	int				num_sprite;
	double			sprite_x;
	double			sprite_y;
	double			inv;
	double			right_left;
	double			ahead_behind;
	int				sprite_center_x;
	int				draw_start_x;
	int				draw_start_y;
	int				draw_end_x;
	int				draw_end_y;
	int				sprite_height;
	int				sprite_width;
	int				screenshot;
	int				*pixel_buf;
}					t_vars;

void				my_mlx_pixel_put(t_vars *vars, int x, int y, char *addr);
void				arg_error_check(t_vars *game, int argc, char **argv);
void				sprite_draw(t_vars *vars, double *z_buffer);
void				set_screen_vars(t_vars *game, t_cub *scene);
void				set_player_vars(t_vars *game, t_cub *scene);
void				draw_floor_ceiling(t_vars *game, char area);
void				set_tex_vars(t_vars *game, t_cub *scene);
void				game_loop(t_vars *game, t_cub *scene);
void				sprite_translate(t_vars *vars, int i);
int					release(int keycode, t_vars *player);
void				set_map(t_vars *game, t_cub *scene);
int					push(int keycode, t_vars *player);
void				raydir_deltadist(t_vars *game);
void				set_sprite_vars(t_vars *vars);
void				look_right_left(t_vars *game);
int					save_screenshot(t_vars *game);
void				drawing_specs(t_vars *game);
void				set_wall_tex(t_vars *game);
void				sprite_dist(t_vars *game);
void				sprite_sort(t_vars *game);
void				draw_scene(t_vars *game);
void				move_right(t_vars *game);
void				move_back(t_vars *game);
void				move_left(t_vars *game);
void				move_fwd(t_vars *game);
void				sidedist(t_vars *game);
void				wall_hit(t_vars *game);
int					exit_game(void);

#endif
