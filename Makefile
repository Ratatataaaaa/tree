NAME = tree
SRC = tree.c
FLAGS = -Wall -Wextra -Werror
OBG = $(SRC:.c=.o)

GREEN = \033[0;32;1m
RED = \033[0;31;1m
RESET = \033[0m

all: $(NAME)

%.o: %.c
	@printf "$(RED)[ft_ls] Compiling [...]\r"
	@gcc $(FLAGS) -c $< -o $@
	@printf "$(GREEN)[ft_ls] Compiling [!!!]\r$(RESET)"

$(NAME): $(OBG)
	@gcc $(FLAGS) $(OBG) -o $(NAME)
	@printf "$(GREEN)[ft_ls] Compiled successfuly! [OK]$(RESET)\n"

clean:
	@/bin/rm -f $(OBG)
	@printf "$(RED)[ft_ls] Removed object files!$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)[ft_ls] Deleted successfuly! [OK]\n$(RESET)"

re: fclean all

mm:
	@$(MAKE) fclean
	@$(MAKE) all
	@$(MAKE) clean

.PHONY: all clean fclean re mm