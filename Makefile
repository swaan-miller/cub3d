# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: smiller <smiller@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2020/08/31 10:13:27 by smiller       #+#    #+#                  #
#    Updated: 2020/11/11 10:58:38 by smiller       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra
NAME = cub3D
HEADER_CUB3D = includes/cub3d.h
HEADER_PARSER = includes/parse.h
LIBFT_DIR = libft
LIBFT = libft.a
MLX_DIR = mlx
MLX = libmlx.dylib
GREEN   = \033[1;38;5;43m
RESET   = \033[0m
RAYCASTER = src_raycstr/driver.c\
			src_raycstr/movement.c\
			src_raycstr/set_vars.c\
			src_raycstr/set_tex_vars.c\
			src_raycstr/raycast_scene.c\
			src_raycstr/raycast_sprite.c\
			src_raycstr/utils.c\
			src_raycstr/bmp.c\
			src_raycstr/keys.c\
			src_raycstr/main.c\

PARSER = 	src_parser/parser_res.c\
		 	src_parser/floor_ceiling_paths.c\
		 	src_parser/check_map.c\
		 	src_parser/array.c\
		 	src_parser/error_checks.c\

all: $(NAME)

$(NAME): $(PARSER) $(RAYCASTER) $(HEADER_CUB3D) $(HEADER_PARSER)
	@$(MAKE) -C $(LIBFT_DIR) && mv $(LIBFT_DIR)/$(LIBFT) .
	@$(MAKE) -C $(MLX_DIR) && mv $(MLX_DIR)/$(MLX) .
	@$(CC) $(CFLAGS) -O3 -L. -lft -lmlx $(PARSER) $(RAYCASTER) -o $(NAME)
	@echo "$(GREEN)./cub3d executable created.$(RESET)"

clean:
	@rm -f $(LIBFT) $(MLX)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@echo "$(GREEN)cleaning libft and mlx.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)deleted ./cub3D executable $(RESET)"

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
