NAME		= cub3D
NAME_BONUS	= cub3D_bonus

CC			= cc
CFLAGS		= -Wall -Werror -Wextra
LDFLAGS 	= -L/usr/X11/lib -lX11 -lXext -lm

LIB_DIR		= mylib
LIB			= $(LIB_DIR)/myLib.a

MLX_DIR 	= /home/hbousset/minilibx/
MLX 		= $(MLX_DIR)/libmlx.a

SRCS 		=	src/parsing/load_file.c src/parsing/parse_file.c \
				src/parsing/parse_identifiers.c \
				src/parsing/validate_wall.c src/parsing/parse_map.c \
				src/parsing/extract_map.c src/main.c src/game_loop.c \
				src/parsing/init_data.c src/raycast.c \
				src/draw_wall.c src/manage_player.c

SRCS_BONUS 	=	src_bonus/parsing/load_map_bonus.c \
				src_bonus/parsing/parse_file_bonus.c \
				src_bonus/parsing/parse_identifiers_bonus.c \
				src_bonus/parsing/validate_wall_bonus.c \
				src_bonus/parsing/parse_map_bonus.c \
				src_bonus/parsing/extract_map_bonus.c \
				src_bonus/game_loop_bonus.c \
				src_bonus/parsing/init_data_bonus.c \
				src_bonus/raycast_bonus.c \
				src_bonus/main_bonus.c src_bonus/draw_wall_bonus.c \
				src_bonus/manage_player_bonus.c \
				src_bonus/minimap_bonus.c src_bonus/doors_bonus.c

OBJS		= $(SRCS:.c=.o)
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

INC_DIR			= inc
HEADER			= $(INC_DIR)/cub3D.h
HEADER_BONUS	= $(INC_DIR)/cub3D_bonus.h

all: $(LIB) $(NAME)

$(LIB):
	@$(MAKE) -s -C $(LIB_DIR)

%.o: %.c $(HEADER) $(HEADER_BONUS)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(NAME): $(OBJS) $(LIB) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) $(MLX) $(LDFLAGS) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS) $(LIB) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIB) $(MLX) $(LDFLAGS) -o $(NAME_BONUS)

bonus: $(NAME_BONUS)

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)
	@$(MAKE) -s clean -C $(LIB_DIR)
	@echo "clean completed \033[1;34m✔\033[0m"

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -s fclean -C $(LIB_DIR)
	@echo "full clean completed \033[1;31m✔\033[0m"

re: fclean all

.PHONY: all clean fclean re bonus
