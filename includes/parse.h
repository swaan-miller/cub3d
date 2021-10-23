/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smiller <smiller@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/21 13:01:07 by smiller       #+#    #+#                 */
/*   Updated: 2020/11/11 10:45:15 by smiller       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define ERROR -1
# define SUCCESS 1
# define ON 1
# define OFF 0
# define WALL 1
# define FILL 'x'
# define SPACE ' '

typedef struct			s_rgb
{
	int					red;
	int					green;
	int					blue;
	int					error;
}						t_rgb;

typedef struct			s_id
{
	char				res;
	char				floor;
	int					ceiling;
	int					count;
}						t_id;

typedef struct			s_path
{
	int					len;
	char				*nrth;
	char				*south;
	char				*wst;
	char				*east;
	char				*sprt;
}						t_path;

typedef struct			s_array
{
	char				*buf;
	char				*str;
	char				*tmp;
	int					len;
	char				start_dir;
	int					start_x;
	int					start_y;
	int					line_count;
	int					longest;
}						t_array;

typedef struct			s_cub
{
	char				*line;
	int					ret;
	int					fd;
	unsigned long long	*res;
	unsigned long long	res_width;
	unsigned long long	res_height;
	char				**map;
	int					newline;
	char				error[3];
	t_rgb				*ptr;
	t_rgb				ceiling;
	t_rgb				floor;
	t_id				typeid;
	t_path				path;
	t_array				array;
	int					num_sprites;
}						t_cub;

int						error(char *reason);
void					parse_cub(t_cub *scene);
void					skip_spaces(char **line);
void					check_elements(t_cub *scene);
int						set_res(t_cub *scene, char **line);
int						set_path(t_cub *scene, char *line);
int						check_map(t_cub *scene, char *line);
void					check_xpm(t_cub *scene, char **path);
void					check_png(t_cub *scene, char **path);
void					allocate_array(t_cub *scene, int x, int y);
int						set_floor_ceiling(t_cub *scene, char *line);
void					check_flood_fill(t_cub *scene, int x, int y);
void					flood_fill(t_cub *scene, int x, int y, char color);

#endif
