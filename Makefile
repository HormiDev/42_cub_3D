# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/12 12:36:27 by ide-dieg          #+#    #+#              #
#    Updated: 2025/12/17 13:36:49 by ide-dieg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

G = \033[1;32m
Y = \033[1;33m
R = \033[0;31m
NC = \033[0m

NAME = cub3D

SRC		=	src/main.c \
			src/game/ft_controls.c \
			src/game/ft_directions.c \
			src/utils/ft_angle_utils.c \
			src/parse/ft_check_args.c \
			src/parse/ft_parse_map.c \
			src/parse/ft_parse_colors.c \
			src/parse/ft_parse_map_utils.c \
			src/parse/ft_check_map.c \
			src/parse/ft_create_game_map.c \
			src/parse/ft_map_origin.c \
			src/parse/ft_walls_closed.c \
			src/parse/ft_read_textures.c \
			src/parse/ft_parse_textures.c \
			src/raycast/ft_calculate_raycasts.c \
			src/render/map_utils.c \
			src/render/ft_paint.c \
			src/render/raycast_utils.c \
			src/render/ft_map2D.c \
			src/ft_sqrt.c \
			src/ft_sin_cos.c \
			src/ft_loading_game.c \
			src/ft_close_game.c \
			src/ft_config_player.c \
			src/ft_config_mlx.c \
			src/ft_mix_color_precalc.c \
			src/ft_mix_color.c \
			src/ft_update.c \
			src/ft_get_time.c \
			src/DEBUG/ft_debug_textures.c \
			src/ft_scale_t_image_precalc.c \
			src/ft_scale_t_image.c \

SRC_BONUS =	src_bonus/main.c \
			src_bonus/game/ft_controls.c \
			src_bonus/game/ft_directions.c \
			src_bonus/game/ft_gamepad.c \
			src_bonus/game/mouse.c \
			src_bonus/game/audio_manager.c \
			src_bonus/game/input_manager.c \
			src_bonus/utils/ft_angle_utils.c \
			src_bonus/utils/ft_vector_utils.c \
			src_bonus/parse/ft_check_args.c \
			src_bonus/parse/ft_parse_map.c \
			src_bonus/parse/ft_parse_colors.c \
			src_bonus/parse/ft_parse_map_utils.c \
			src_bonus/parse/ft_check_map.c \
			src_bonus/parse/ft_create_game_map.c \
			src_bonus/parse/ft_map_origin.c \
			src_bonus/parse/ft_walls_closed.c \
			src_bonus/parse/ft_read_textures.c \
			src_bonus/parse/ft_parse_textures.c \
			src_bonus/raycast/ft_calculate_raycasts.c \
			src_bonus/raycast/ft_raycast.c \
			src_bonus/raycast/ft_raycast_utils.c \
			src_bonus/render/map_utils.c \
			src_bonus/render/ft_paint.c \
			src_bonus/render/raycast_utils.c \
			src_bonus/render/ft_map2D.c \
			src_bonus/ft_sqrt.c \
			src_bonus/ft_image_transparent.c \
			src_bonus/ft_play_audio.c \
			src_bonus/ft_sin_cos.c \
			src_bonus/ft_loading_game.c \
			src_bonus/ft_close_game.c \
			src_bonus/ft_config_player.c \
			src_bonus/ft_config_mlx.c \
			src_bonus/ft_mix_color_precalc.c \
			src_bonus/ft_mix_color.c \
			src_bonus/ft_update.c \
			src_bonus/DEBUG/ft_debug_textures.c \
			src_bonus/ft_get_time.c \
			src_bonus/ft_scale_t_image_precalc.c \
			src_bonus/ft_scale_t_image.c \
			src_bonus/ft_precalc_rotated_squares.c \
			src_bonus/ft_menu.c \
			src_bonus/ft_prec_fish_eye_correction.c \
			src_bonus/ft_prec_vector_cloud.c \
			src_bonus/objects/door.c \
			src_bonus/objects/door_utils.c \
			src_bonus/objects/door_raycast.c \
			src_bonus/ft_resolutions.c \

OBJ_DIR  = objects
OBJ_DIR_BONUS  = objects_bonus

LIBSA = minilibx-linux/libmlx.a \
		42_Libft/libft.a \

LFLAGS = -lXext -lX11 -lm

OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
OBJ_BONUS = $(patsubst %.c, $(OBJ_DIR_BONUS)/%.o, $(SRC_BONUS))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3  #-fsanitize=address

all: clear $(NAME) title_print

bonus: clear build_bonus title_print

update_submodules:
	@echo "$(Y)----------------------------------------------------------------------------------------------------$(NC)"
	@echo "$(Y)-----------------------------------------Updating submodules----------------------------------------$(NC)"
	@echo "$(Y)----------------------------------------------------------------------------------------------------$(NC)\n"
	@git submodule update --init --recursive > /dev/null 2>&1
	@tput cuu1 && tput el
	@tput cuu1 && tput el
	@tput cuu1 && tput el
	@tput cuu1 && tput el
	@tput cuu1 && tput el
	@echo "$(G)----------------------------------------------------------------------------------------------------$(NC)"
	@echo "$(G)---------------------------------------- Submodules updated! ---------------------------------------$(NC)"
	@echo "$(G)----------------------------------------------------------------------------------------------------$(NC)\n"

clear:
	clear

$(NAME): update_submodules build_libft build_minilibx-linux $(OBJ)
	@printf "%-183s\r" "" 
	@$(CC) $(CFLAGS) $(OBJ) $(LIBSA) $(LFLAGS) -o $(NAME)
	@tput cuu1 && tput el
	@tput cuu1 && tput el
	@tput cuu1 && tput el
	@tput cuu1 && tput el
	@if [ -f $(NAME) ]; then \
		echo "$(G)----------------------------------------------------------------------------------------------------$(NC)"; \
		echo "$(G)------------------------------------------ CUB3D Compiled! -----------------------------------------$(NC)"; \
		echo "$(G)----------------------------------------------------------------------------------------------------\n$(NC)"; \
	else \
		echo "$(R)----------------------------------------------------------------------------------------------------$(NC)"; \
		echo "$(R)--------------------------------------- CUB3D Compilation Failed -----------------------------------$(NC)"; \
		echo "$(R)----------------------------------------------------------------------------------------------------\n$(NC)"; \
	fi

build_bonus: update_submodules build_libft build_minilibx-linux $(OBJ_BONUS)
	@printf "%-183s\r" "" 
	@$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBSA) $(LFLAGS) -o cub3D_bonus
	@tput cuu1 && tput el
	@tput cuu1 && tput el
	@tput cuu1 && tput el
	@tput cuu1 && tput el
	@if [ -f cub3D_bonus ]; then \
		echo "$(G)----------------------------------------------------------------------------------------------------$(NC)"; \
		echo "$(G)--------------------------------------- CUB3D BONUS Compiled! --------------------------------------$(NC)"; \
		echo "$(G)----------------------------------------------------------------------------------------------------\n$(NC)"; \
	else \
		echo "$(R)----------------------------------------------------------------------------------------------------$(NC)"; \
		echo "$(R)----------------------------------- CUB3D BONUS Compilation Failed ---------------------------------$(NC)"; \
		echo "$(R)----------------------------------------------------------------------------------------------------\n$(NC)"; \
	fi

build_libft:
	@if [ ! -f 42_Libft/libft.a ]; then \
		echo "$(Y)----------------------------------------------------------------------------------------------------$(NC)"; \
		echo "$(Y)------------------------------------------ Compiling Libft -----------------------------------------$(NC)"; \
		echo "$(Y)----------------------------------------------------------------------------------------------------\n$(NC)"; \
		make all -C 42_Libft > /dev/null 2>&1; \
		tput cuu1 && tput el; \
		tput cuu1 && tput el; \
		tput cuu1 && tput el; \
		tput cuu1 && tput el; \
		if [ -f 42_Libft/libft.a ]; then \
			echo "$(G)----------------------------------------------------------------------------------------------------$(NC)"; \
			echo "$(G)------------------------------------------ Libft Compiled ------------------------------------------$(NC)"; \
			echo "$(G)----------------------------------------------------------------------------------------------------\n$(NC)"; \
		else \
			echo "$(R)----------------------------------------------------------------------------------------------------$(NC)"; \
			echo "$(R)-------------------------------------- Libft Compilation Failed ------------------------------------$(NC)"; \
			echo "$(R)----------------------------------------------------------------------------------------------------\n$(NC)"; \
		fi; \
	fi

fclean_libft:
	@make fclean -C 42_Libft > /dev/null 2>&1
	@echo "$(R)------------------------------------------ Libft Cleaned -------------------------------------------$(NC)"

build_minilibx-linux:
	@if [ ! -f minilibx-linux/libmlx.a ]; then \
		echo "$(Y)----------------------------------------------------------------------------------------------------$(NC)"; \
		echo "$(Y)------------------------------------- Compiling Minilibx-linux -------------------------------------$(NC)"; \
		echo "$(Y)----------------------------------------------------------------------------------------------------\n$(NC)"; \
		make -C minilibx-linux > /dev/null 2>&1; \
		tput cuu1 && tput el; \
		tput cuu1 && tput el; \
		tput cuu1 && tput el; \
		tput cuu1 && tput el; \
		if [ -f minilibx-linux/libmlx.a ]; then \
			echo "$(G)----------------------------------------------------------------------------------------------------$(NC)"; \
			echo "$(G)------------------------------------- Minilibx-linux Compiled --------------------------------------$(NC)"; \
			echo "$(G)----------------------------------------------------------------------------------------------------\n$(NC)"; \
		else \
			echo "$(R)----------------------------------------------------------------------------------------------------$(NC)"; \
			echo "$(R)--------------------------------- Minilibx-linux Compilation Failed --------------------------------$(NC)"; \
			echo "$(R)----------------------------------------------------------------------------------------------------\n$(NC)"; \
		fi; \
	fi

fclean_minilibx-linux:
	@make -C minilibx-linux clean > /dev/null 2>&1

$(OBJ_DIR):
	@echo "$(Y)----------------------------------------------------------------------------------------------------$(NC)"
	@echo "$(Y)----------------------------------------- Compiling  CUB3D -----------------------------------------$(NC)"
	@echo "$(Y)----------------------------------------------------------------------------------------------------\n$(NC)"
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/src/%.o: src/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -Iincludes -c -o $@ $<

$(OBJ_DIR_BONUS):
	@echo "$(Y)----------------------------------------------------------------------------------------------------$(NC)"
	@echo "$(Y)-------------------------------------- Compiling  CUB3D BONUS --------------------------------------$(NC)"
	@echo "$(Y)----------------------------------------------------------------------------------------------------\n$(NC)"
	@mkdir -p $(OBJ_DIR_BONUS)

$(OBJ_DIR_BONUS)/src_bonus/%.o: src_bonus/%.c | $(OBJ_DIR_BONUS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -Iincludes -c -o $@ $<

clean: clear
	@rm -rf $(OBJ_DIR)
	@rm -fr $(OBJ_DIR_BONUS)
	@echo "$(R)----------------------------------------- Objects  Cleaned -----------------------------------------$(NC)"

fclean: clean fclean_libft fclean_minilibx-linux
	@rm -f $(NAME)
	@rm -f cub3D_bonus
	@echo "$(R)------------------------------------------ CUB3D Is Clean ------------------------------------------\n$(NC)"

re: fclean $(NAME) title_print

rebonus: fclean bonus title_print

title_print:                                                                                                                
	@echo "$(G)                                         ..:-+**#*+:.                                              $(NC)"
	@echo "$(G)                                     ..-##%%%%%%%%%#*-.                                            $(NC)"
	@echo "$(G)                                  ..=%%@@@@@@@@@%##%%#:                                            $(NC)"
	@echo "$(G)                                 .*#@@@@@@@%@@@%%%%%%#.                                            $(NC)"
	@echo "$(G)                               .#@@@@@%@@@@@%%%%%#%#*.                                             $(NC)"
	@echo "$(G)                             .+@@@@@@@@%%%%%%%%%%%=..    .-#%:                                     $(NC)"
	@echo "$(G)                            -%@@@@@@@@%%%%%%%%*..      .%@@@%#.                                    $(NC)"
	@echo "$(G)                          .*@@@@@@@@@@%%%%+:..        :@%+...                                      $(NC)"
	@echo "$(G)                         .#@@@@@@@@%@@@%=.        .-.+@@%:  ..   :*%%:                             $(NC)"
	@echo "$(G)                        :%@@@@@@%@@@@@@=+#%%%%#=:*+%@@@@...=+  -%@@#=:.                            $(NC)"
	@echo "$(G)                       :%@@@@@@@@@%@@@@@%%@@%%%%%%%%%@@@%#+:..=@%#.                                $(NC)"
	@echo "$(G)                      .#%@@@@@@@@@@@@@@@%@@@@@%@%%%#%%%#*-:=*%@%@+                                 $(NC)"
	@echo "$(G)                     .+%@@@@@@@@@@@@@@@@@@%%@@@@@@%%%%%%@%@@@@%@@:                                 $(NC)"
	@echo "$(G)                     -%%@@@@@@%@@@@@@@@@@@@@@@@@@@%%%%%*%%%%%@@@:                                  $(NC)"
	@echo "$(G)                    .#%%@@@@@@@@@@@@@@@@@@%@@@@@@@@@@@%#*#%%@@@%=.+.                               $(NC)"
	@echo "$(G)                   .=%%%%%%@@@@@%%%@%%%%%%%%@@@@@@@@@@@@%##%@@@@%+*.                               $(NC)"
	@echo "$(G)                   .#%@%%%%%%%%%%%%%%%%%%%%%%@@@@@@@@@@@@%%%#%@@@@-.                               $(NC)"
	@echo "$(G)             .     :#%%%@%%%%%%%##..#%%#%#%%%%%@@@@@@@@@@@@%%%%@@@%:.                              $(NC)"
	@echo "$(G)             .     :%%@@@%%%%%%%%:   .+#*+*##%%%%%%@@@@@@@@@%@@@%#+*=.                             $(NC)"
	@echo "$(G)            ..     .#%@@%%%#%%%##.     ..--+*#%%%%%@@@@@@@@%%@@@@@%=:.                             $(NC)"
	@echo "$(G)            -.     .-%@@@%#+-=%%*.        .+**#%%%%@@@@@@@@@@#%@@@@%+*.                            $(NC)"
	@echo "$(G)           .#.       -@@@%=:=%%%.         -###%%%%%%%%@@@@@@@@@@@@@@@@###*+*.                      $(NC)"
	@echo "$(G)           **.        .+*-..#%%#          .:+#%%%%%%%@@@@@@@%%@@@@@@@#:                            $(NC)"
	@echo "$(G)        :%@%.              .:=%+            ..:=+###@%@@@@@#%@@@@@@@@%+#=                          $(NC)"
	@echo "$(G)       .#@@=                  ..                   ....:=*#@@@@@@@@@@@@%#*-: .                     $(NC)"
	@echo "$(G)      .:%%%-                                            .+%@@@@@@@@@@@@@@%%@@@%%.                  $(NC)"
	@echo "$(G)     .%@@+-.                                    ..:==*##%@@@@@@@@@@@%%@@%%@@@#-.                   $(NC)"
	@echo "$(G)     .%@%*=-                              .:=*#%@@@@@@%@@@@@@@@@@@@@@@%%%@@@@%*=**-.               $(NC)"
	@echo "$(G)    .@@@*=#-                          ..+%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%-             $(NC)"
	@echo "$(G)    .#@@*...                        .-%@@@@@@@@@@@@%@@@@@@@@@@@@@@@@@@@@@@%@@@@@@@-:.              $(NC)"
	@echo "$(G)    -@@%-*+-                     .:*%%@@@@@@@@@@@%@@@@@@@@@@@@@@@@@@@@@@@@@@%@@@@@+                $(NC)"
	@echo "$(G)    .%@@*.:..                   .+%@@@@@@@@@@@@@#@@@@@@@@@@@@@@@@@@@@@@@#.:#@@@@@@#-:.             $(NC)"
	@echo "$(G)    .*@@*=%-.                  .*%@@@@@@@@@@@@@#@@@@@@@@@@@@@@@@@@@@@@%#.   -%@@@@@@@+.            $(NC)"
	@echo "$(G)    .#@@@+.::..                 :@@@@@@@@@@@@@@%@@@@%@@@@@@@@@@@@@@@*.       +%@@@@@%@+.           $(NC)"
	@echo "$(G)      +@@*:@=.                  .%%@@%%%%@@@@@@@@@@@@@@@@@@@@@@@@@@*...        .#%@@@%: ...        $(NC)"
	@echo "$(G)      +@@@%.....                   %@@%%%%@@@@=@@@#%@@@@@@@@@@@@@@@%:*@@@=       .%@@@@@@.         $(NC)"
	@echo "$(G)      .+@@@:+#..                     %@@%%%%@@@@@:@:+     .....:%@@@@@@@@@+        *@@@@@@@+.      $(NC)"
	@echo "$(G)       .-@@@%..#%-                       %@@%%%%@@@@          .:@@@@@@@-            .#@@@@@@#.     $(NC)"
	@echo "$(G)        .*@@@#.+*.                         .@%.-%.%:            =@@@@@@:             ..%@@@@@#.    $(NC)"
	@echo "$(G)         ..+@@@@%=.*%.                     .%@: :%.=.           :@@@@@%.              .*@@@@@@%.   $(NC)"
	@echo "$(G)           .=%@@@@@+.                     :@@. :%.            .:@@@..                  :+@@@@@@*.  $(NC)"
	@echo "$(G)             .-@@@%..#%-                     .:.@ .+:            ..:@@@..               .#@@@@@*=  $(NC)"
	@echo "$(G)                 @@@%..#%                     ..@  .:..           ..:@@@..             .*@@@@@@%.  $(NC)"
	@echo "$(G)                  *##%@@@..#%                                                         .#%@@@%: .   $(NC)"
	@echo "$(G)                      *##%@@@@@.                                                   -%@@@@@:        $(NC)"
	@echo "$(G)                         .-@@@@%@@@@                                           .-@@@@%@..          $(NC)"
	@echo "$(G)                                :%.=@@@@%@@                          .    *@@@@@@%:.               $(NC)"
	@echo "$(G)                                     ###*##%@@@@@.-@@@%..#%--@@@%..#%-#@@@@@*:.                    $(NC)"
	@echo "$(G)                                           *##%@@@@@.-@@@%..#%-.#@:::.                             $(NC)"
	@echo "$(G)                                                                                                   $(NC)"									
	@echo "	                                $(Y)ide-dieg $(G)/ $(R)ismherna$(NC)"
	@echo "$(NC)\n"


                                                
norm: clearif

.PHONY: all clean fclean re clear title_print bonus rebonus