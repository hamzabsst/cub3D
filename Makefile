NAME	= cub3D
CC		= cc
CFLAGS	= -Wall -Werror -Wextra

LIB_DIR	= mylib
LIB		= $(LIB_DIR)/myLib.a

SRCS 	= src/main.c
OBJS	= $(SRCS:.c=.o)

INC_DIR	= inc
HEADERS	= $(INC_DIR)/cube3D.h

all: $(LIB) $(NAME)

$(LIB):
	@$(MAKE) -s -C $(LIB_DIR)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(NAME): $(OBJS) $(LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)

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
