# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/25 18:27:37 by mpetruno          #+#    #+#              #
#    Updated: 2019/02/28 18:21:55 by mpetruno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

FLAGS = -Wall -Werror -Wextra -g

SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./includes/
LIB_DIR = ./libft/
BUILTIN_DIR = builtin/
LIB_INC_DIR = $(LIB_DIR)includes/
LIB = $(LIB_DIR)libft.a

DIR_LST = $(OBJ_DIR) \
			$(OBJ_DIR)$(BUILTIN_DIR) \
			$(OBJ_DIR)hashmap/ \
			$(OBJ_DIR)env/ \
			$(OBJ_DIR)err/ \
			$(OBJ_DIR)lex/ \
			$(OBJ_DIR)parser/ \
			$(OBJ_DIR)exec/ \
			$(OBJ_DIR)ast/ \
			$(OBJ_DIR)shell/ \
			$(OBJ_DIR)sig/ \
			$(OBJ_DIR)ui/ \
			$(OBJ_DIR)ui/cursor \
			$(OBJ_DIR)ui/term/ \
			$(OBJ_DIR)ui/history/ \
			$(OBJ_DIR)ui/input/ \
			$(OBJ_DIR)ui/autocmp/

MAIN_FILES = main.c \
			\
			hashmap/hashmap.c \
			hashmap/hm_util.c \
			\
			exec/expansion.c \
			exec/tkn_add.c \
			exec/expand_str.c \
			exec/execute.c \
			exec/exec_cmd.c \
			exec/get_argv.c \
			exec/redirect.c \
			exec/io_backup.c \
			\
			err/err.c \
			\
			ast/tree.c \
			ast/exec_node.c \
			\
			sig/signal.c \
			\
			env/environ.c \
			env/environ_util.c \
			\
			lex/lexer.c \
			lex/lexer_util.c \
			lex/heredoc.c \
			\
			parser/parser.c \
			\
			shell/shell.c \
			shell/shell_exit.c \
			shell/binary.c \
			\
			ui/input/buffer.c \
			ui/input/read_inp.c \
			ui/input/read_symbol.c \
			ui/input/insert.c \
			ui/input/control.c \
			ui/input/move.c \
			ui/input/smart_move.c \
			ui/input/delete.c \
			ui/input/copy.c \
			ui/input/cut.c \
			ui/input/paste.c \
			ui/input/eof.c \
			\
			ui/history/history.c \
			ui/history/navigate.c \
			ui/history/search.c \
			\
			ui/autocmp/autocomp.c \
			ui/autocmp/print_options.c \
			ui/autocmp/refresh_ui.c \
			ui/autocmp/file_comp.c \
			ui/autocmp/exec_comp.c \
			ui/autocmp/find_exec.c \
			\
			ui/term/config.c \
			ui/term/output.c \
			\
			ui/cursor/move.c \
			ui/cursor/set.c \
			ui/util.c \
			ui/prompt.c


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

$(NAME): $(LIB) $(DIR_LST) $(OBJ_LIST)
	@$(CC) $(OBJ_LIST) $(LIB) -o $(NAME) -ltermcap
	@echo "$(NAME) - Done."

$(LIB):
	@make -C $(LIB_DIR) all --silent

$(DIR_LST):
	@mkdir -p $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(FLAGS) -I $(INC_DIR) -I $(LIB_INC_DIR) -c $^ -o $@


clean:
	@echo "$(NAME): Cleaning object files... "
	@rm -rf $(OBJ_DIR)
	@make -C $(LIB_DIR) clean --silent

fclean: clean
	@echo "$(NAME): Removing $(NAME)... "
	@rm -f $(NAME)
	@make -C $(LIB_DIR) fclean --silent

re: fclean all

.PHONY = all clean fclean re
