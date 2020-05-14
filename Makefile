NAME = tree
SRC = tree.c
FLAGS = -Wall -Wextra -Werror
OBG = $(SRC:.c=.o)

GREEN = \033[0;32;1m
RED = \033[0;31;1m
RESET = \033[0m

all: $(NAME)

%.o: %.c
	@printf "$(RED)[tree] Compiling [...]\r"
	@gcc $(FLAGS) -c $< -o $@
	@printf "$(GREEN)[tree] Compiling [!!!]\r$(RESET)"

$(NAME): $(OBG)
	@gcc $(FLAGS) $(OBG) -o $(NAME)
	@printf "$(GREEN)[tree] Compiled successfuly! [OK]$(RESET)\n"

clean:
	@/bin/rm -f $(OBG)
	@printf "$(RED)[tree] Removed object files!$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)[tree] Deleted successfuly! [OK]\n$(RESET)"

re: fclean all

mm:
	@$(MAKE) fclean
	@$(MAKE) all
	@$(MAKE) clean

.PHONY: all clean fclean re mm