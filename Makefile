FT_SSL = ft_ssl

G = -g
FSAN = -fsanitize=address $(G)
FLAGS = -Wall -Werror -Wextra

SRCS_DIR = src/
OBJS_DIR = obj/

INC = inc/
HEADER = $(INC)ft_ssl.h

LIBFT = libft/ft_printf
LIBFT_A = $(LIBFT)/libftprintf.a

SRCS_FILES = ft_ssl.c \
	read.c \
	print.c \
	md5.c \
	md5_rotate.c \
	sha.c \
	sha_chunk.c \
	sha_cmd.c \
	sha512.c

SRCS_PATH = $(SRCS_FILES:%=$(SRCS_DIR)%)

OBJS = $(SRCS_FILES:%.c=%.o)
OBJS_PATH = $(addprefix $(OBJS_DIR), $(OBJS))

GREEN = "\033[0;32m"
RED = "\033[0;31m"
DEFAULT = "\033[0m"

all: comp_libft $(FT_SSL)

comp_libft:
	@make -C $(LIBFT)

norm:
	norminette $(INC) $(SRCS_DIR) $(SHARED) libft/

fsanitize:
	@echo $(RED)"Compiling all with -g and -fsanitize:" $(FT_SSL) $(DEFAULT)
	make -C $(LIBFT)/ fsanitize
	gcc $(FLAGS) $(FSAN) -c $(SRCS_PATH) -I $(INC)
	mkdir -p $(OBJS_DIR)
	mv $(OBJS) $(OBJS_DIR)
	gcc $(FLAGS) $(FSAN) $(OBJS_PATH) $(LIBFT_A) -o $(FT_SSL) -I $(LIBFT) -I $(INC)

$(FT_SSL): $(LIBFT_A) $(OBJS_DIR) $(OBJS_PATH)
	@echo "Compiling:" $(GREEN) $(FT_SSL) $(DEFAULT)
	gcc $(G) $(FLAGS) $(OBJS_PATH) $(LIBFT_A) -o $(FT_SSL) -I $(LIBFT) -I $(INC)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER)
	@echo "Compiling:" $(GREEN) $< $(DEFAULT)
	gcc $(G) $(FLAGS) -c $< -o $@ -I $(INC)

clean:
	@make -C $(LIBFT)/ clean
	@rm -rf $(OBJS_DIR)

fclean:
	@make -C $(LIBFT)/ fclean
	@rm -rf $(OBJS_DIR) $(FT_SSL)

re: fclean all

.PHONY: all comp_libft clean fclean re
