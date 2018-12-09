# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/25 18:27:37 by mpetruno          #+#    #+#              #
#    Updated: 2018/12/06 18:59:56 by mpetruno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

FLAGS = -Wall -Werror -Wextra

SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./includes/
LIB_DIR = ./libft/
BUILTIN_DIR = builtin/
LIB_INC_DIR = $(LIB_DIR)includes/
LIB = $(LIB_DIR)libft.a

MAIN_FILES = main.c \
			execute.c \
			signal.c \
			environ.c \
			environ_util.c \
			lexer.c \
			lexer_util.c \
			parser.c \
			free_util.c \
			err.c \
			on_key.c \
			input.c \
			input_buff.c \
			input_buff_manage.c \
			autocompl.c \
			aux.c \
			shell/shell.c \
			shell/terminal.c \
			shell/shell_init.c \
			shell/shell_exit.c



BUILTIN = builtin.c \
			exit.c \
			pwd.c \
			cd.c \
			env.c \
			setenv.c \
			unsetenv.c \
			echo.c

SRC_LIST = $(MAIN_FILES) \
			$(addprefix $(BUILTIN_DIR), $(BUILTIN))

OBJ_LIST = $(addprefix $(OBJ_DIR), $(SRC_LIST:.c=.o))

all: $(NAME)

$(NAME): $(LIB) create_directories $(OBJ_LIST)
	@$(CC) $(OBJ_LIST) $(LIB) -o $(NAME) -L ./ -ltermcap
	@echo "$(NAME) - Done."

$(LIB):
	@make -C $(LIB_DIR) all --silent

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(FLAGS) -I $(INC_DIR) -I $(LIB_INC_DIR) -c $^ -o $@

create_directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(BUILTIN_DIR)
	@mkdir -p $(OBJ_DIR)shell/

clean:
	@echo "$(NAME): Cleaning object files... "
	@rm -rf $(OBJ_DIR)
	@make -C $(LIB_DIR) clean --silent

fclean: clean
	@echo "$(NAME): Removing $(NAME)... "
	@rm -f $(NAME)
	@make -C $(LIB_DIR) fclean --silent

re: fclean all

.PHONY = all clean fclean re create_directories
