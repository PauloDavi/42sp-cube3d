vpath %.c src/mandatory
vpath %.c src/bonus

NAME := cub3D
CFLAGS := -Wextra -Wall -Werror
CFLAGS += -g3

CC := cc
RM := rm -rf

LIBTF_DIR := ./lib/libft
LIBMLX := ./lib/MLX42
LIBS := -L$(LIBTF_DIR) -lft $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

OBJ_DIR := build
INCLUDE_DIR := include
INCLUDES := -I$(INCLUDE_DIR) -I$(LIBTF_DIR) -I$(LIBMLX)/include

SRCS := cub3d.c map.c init.c draw.c utils.c finish.c validation.c read_param.c
SRCS += player.c load_params.c math_utils.c rays.c walls.c
OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

SRCS_BONUS := cub3d_bonus.c door_bonus.c draw_bonus.c finish_bonus.c init_bonus.c
SRCS_BONUS += load_params_bonus.c map_bonus.c math_utils_bonus.c mini_map_bonus.c
SRCS_BONUS += player_bonus.c rays_bonus.c read_param_bonus.c utils_bonus.c sprits_bonus.c
SRCS_BONUS += validation_bonus.c walls_bonus.c
OBJS_BONUS := $(addprefix $(OBJ_DIR)/, $(SRCS_BONUS:.c=.o))

all: update_submodules libft mlx $(NAME)

init_submodules:
	git submodule update --init

update_submodules: init_submodules
	git submodule foreach git pull origin master

libft:
	@$(MAKE) -C $(LIBTF_DIR)

mlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(INCLUDES) $(CFLAGS) -o $(NAME)

bonus: update_submodules libft mlx $(OBJS_BONUS)
	@$(CC) $(OBJS_BONUS) $(LIBS) $(INCLUDES) $(CFLAGS) -o $(NAME)

clean: 
	@$(MAKE) -C $(LIBTF_DIR) clean
	@$(RM) -rf $(LIBMLX)/build
	@$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	@$(MAKE) -C $(LIBTF_DIR) fclean
	@$(RM) $(NAME)

re: fclean all

rebonus: fclean bonus

run: all
	./$(NAME) maps/map.cub

bun: bonus
	./$(NAME) maps/map_bonus.cub

check: all
	valgrind -q --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --suppressions=suppress.sup ./$(NAME) maps/map.cub

bheck: bonus
	valgrind -q --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --suppressions=suppress.sup ./$(NAME) maps/map_bonus.cub

.PHONY: all clean fclean re bonus rebonus libft update_modules init_modules
