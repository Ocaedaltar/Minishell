# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/18 12:05:06 by mlormois          #+#    #+#              #
#    Updated: 2021/09/14 18:56:46 by mlormois         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

export CPPFLAGS="-I/Users/$(USER)/.brew/opt/readline/include"
export LDFLAGS="-L/Users/$(USER)/.brew/opt/readline/lib"

NAME		=	minishell

# --   Directory   -- #
OBJ_DIR     =   ./objs
LIB_DIR		=   ./libft
INC_DIR		=	./incs
INC_LIB_DIR =	./libft/incs

# --  Search All files in SRCS  -- #
SRC_DIR = $(shell find srcs -type d)
vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)
SRCS =    main.c \
        shell_ast.c \
        shell_spliter.c \
        shell_tokenizer.c \
        ft_ast_lst.c \
        ft_ast_setpipe.c \
        ft_cli_lst.c \
        add_variable.c \
        shell_expension.c \
        expension_utils.c \
        utils_wildcard.c \
        add_wildcard.c \
        matching_wildcard_algorithm.c \
        ft_display.c \
        ft_ismetachar.c \
        signal_handler.c \
        ft_check_file.c \
        ft_list_to.c \
        ft_token_lst.c \
        ft_token_utils.c \
        ft_lst_split.c \
        ft_error_plus.c \
        ft_error.c \
        ft_error_syntax.c \
        ft_handler_getenv.c \
        ft_getenv.c \
        ft_utils_getenv.c \
        ft_redirection_loader.c \
        shell_exec.c \
        ft_here_doc.c \
        utils_exec.c \
		ft_bulltin_fork.c \
        ft_cd.c \
        ft_env.c \
        ft_pwd.c \
        ft_export.c \
        ft_echo.c \
        ft_exit.c \
        ft_unset.c \

# $(foreach dir, $(SRC_DIR), $(foreach file, $(wildcard $(dir)/*.c), $(notdir $(file))))

# --  Redirection in OBJS  -- #
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

# --   Compilation flags  -- #
CC			=	gcc
CFLAGS      =   -Wall -Wextra -Werror

# --  Animation Calcul %  -- #
T = $(words $(OBJS) 0)
N = 0
C = $(words $N)$(eval N := x $N)
ECHO = "[`expr $C '*' 100 / $T`%]"

# --  Color   -- #
_CYAN  = \033[36m
_GREEN = \033[32m
_RED   = \033[31m
_ENDL  = \033[0m

UNAME = $(shell uname)

# --  Check OS for Additional Flags %  -- #
ifeq ($(UNAME), Linux)
	OSFLAG = -lreadline
endif
ifeq ($(UNAME), Darwin)
	OSFLAG = $(LDFLAGS) $(CPPFLAGS) -lreadline
	CFLAGS += -g3 -fsanitize=address
endif

.PHONY: all
all :
	@make -C $(LIB_DIR) --no-print-directory
	@make $(NAME) --no-print-directory

$(NAME): $(OBJS) $(INC_DIR)/*.h
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ./libft/libft.a $(OSFLAG)
	@echo "$(_GREEN)[100%] Minishell Compilation Success$(_ENDL)"

$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $< -I $(INC_DIR) -I $(INC_LIB_DIR) $(CPPFLAGS)
	@printf "%-65b\r" "$(_GREEN)$(ECHO)$(_CYAN) Compilation $(notdir $@)"

$(OBJ_DIR) :
	@mkdir -p $@

.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIB_DIR) --no-print-directory
	@echo "$(_RED)[100%]$(_CYAN)  minishell *.o has been cleaned"

.PHONY: fclean
fclean: clean
	@make fclean -C $(LIB_DIR) --no-print-directory
	@rm -f $(NAME)
	@echo "$(_RED)minishell $(_CYAN)   has been cleaned"

.PHONY: re
re: fclean all
