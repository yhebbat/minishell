#PHONY: all clean fclean re

NAME = minishell

SRC =	minishell.c libft0.c ft_split.c toke.c ft_tst.c save_env.c error.c \
		free.c fill_cmd_struct.c ft_strjoin.c redirections.c \
		libft1.c ./execution/builtins.c ./execution/exec.c ./execution/launch.c
#SRC_BONUS =	checker.c get_next_line.c get_next_line_utils.c pile.c \
			operations.c to_check.c utils.c free.c
OBJECT = $(SRC:.c=.o)
#OBJECT_BONUS = $(SRC_BONUS:.c=.o)

all : $(NAME)

$(NAME):
	@gcc $(SRC) -o $(NAME) -g -lreadline -fsanitize=address
	@echo "✅✅✅"

#bonus:
#	@gcc -Wall -Wextra -Werror $(SRC_BONUS) -o $(NAME_BONUS)
#	@echo "🎁🎁🎁"

clean:
	@rm -f $(OBJECT)
	@echo "🗑️ 🗑️ 🗑️"
fclean: clean
	@rm -f $(NAME)
	@echo "🚮🚮🚮"
re: fclean all
