# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 04:10:34 by yhebbat           #+#    #+#              #
#    Updated: 2021/11/24 04:11:20 by yhebbat          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#PHONY: all clean fclean re


#LDFLAGS=-L/home/linuxbrew/.linuxbrew/Cellar/readline/lib
#CPPFLAGS=-I/home/linuxbrew/.linuxbrew/Cellar/readline/include
LDFLAGS=-L/Users/yhebbat/.brew/opt/readline/lib
CPPFLAGS=-I/Users/yhebbat/.brew/opt/readline/include
#LDFLAGS=-L/Users/yhebbat/.brew/opt/readline/lib
#CPPFLAGS=-I/Users/yhebbat/.brew/opt/readline/include

#LDFLAGS=-L/home/linuxbrew/.linuxbrew/Cellar/readline/lib
#CPPFLAGS=-I/home/linuxbrew/.linuxbrew/Cellar/readline/include

NAME = minishell

SRC =	./parsing/minishell.c ./parsing/libft0.c ./parsing/ft_split.c ./parsing/toke.c ./parsing/ft_tst.c ./parsing/save_env.c ./parsing/error.c \
		./parsing/free.c ./parsing/fill_cmd_struct.c ./parsing/ft_strjoin.c ./parsing/redirections.c \
		./parsing/libft1.c ./parsing/error_tools.c ./execution/cd.c ./execution/echo.c ./execution/env.c \
		./execution/execute.c ./parsing/fill_cmd_struct_sec.c ./parsing/fill_cmd_struct_helper.c ./parsing/fill_cmd_struct_tools.c \
		./parsing/ft_flex_helper.c ./parsing/minishell_tools.c ./parsing/save_env_tools.c ./parsing/toke_helper.c \
		./parsing/redirections_helper.c ./parsing/redirections_tool.c ./parsing/redirections_tools.c \
		./execution/exit.c ./execution/export.c ./execution/pipes.c ./execution/pwd.c ./execution/unset.c ./execution/redirection_exec.c \
		./execution/execute_tools.c ./execution/execute_tool.c ./execution/execute_helper.c ./execution/execute_utils.c ./execution/export_utils.c \
		./execution/export_tools.c ./execution/unset_helper.c
#SRC_BONUS =	checker.c get_next_line.c get_next_line_utils.c pile.c \
			operations.c to_check.c utils.c free.c
OBJECT = $(SRC:.c=.o)
#OBJECT_BONUS = $(SRC_BONUS:.c=.o)

all : $(NAME)

$(NAME):
	@gcc -Wall -Werror -Werror $(SRC) -o $(NAME) -lreadline -g $(LDFLAGS) $(CPPFLAGS) #-fsanitize=address  
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
