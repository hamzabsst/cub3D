NAME	= cub3D_bonus
CC		= cc
CFLAGS	= -Wall -Werror -Wextra
LDFLAGS = -L/usr/X11/lib -lX11 -lXext -lm


LIB_DIR	= mylib
LIB		= $(LIB_DIR)/myLib.a

MLX_DIR = minilibx
MLX = $(MLX_DIR)/libmlx.a

SRCS 	=	src/main_bonus.c src/utils_bonus.c src/parsing/load_map_bonus.c src/parsing/parse_file_bonus.c \
			src/parsing/parse_identifiers_bonus.c src/parsing/validate_wall_bonus.c src/parsing/parse_map_bonus.c \
			src/parsing/extract_map_bonus.c src/game_loop_bonus.c src/init_data_bonus.c src/raycast_bonus.c \
			src/draw_wall_bonus.c src/manage_player_bonus.c \

OBJS	= $(SRCS:.c=.o)

INC_DIR	= inc
HEADERS	= $(INC_DIR)/cub3D_bonus.h

all: $(LIB) $(NAME)

$(LIB):
	@$(MAKE) -s -C $(LIB_DIR)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(NAME): $(OBJS) $(LIB) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) $(MLX) $(LDFLAGS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -s clean -C $(LIB_DIR)
	@echo "clean completed \033[1;34m✔\033[0m"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s fclean -C $(LIB_DIR)
	@echo "full clean completed \033[1;31m✔\033[0m"

re: fclean all

.PHONY: all clean fclean re
