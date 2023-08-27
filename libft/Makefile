# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/15 18:03:52 by mlormois          #+#    #+#              #
#    Updated: 2021/09/12 16:09:44 by rmechety         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libft.a

# --   Directory   -- #
OBJ_DIR     =   objs
INC_DIR		=	incs

# --  Search All files in SRCS  -- #
SRC_DIR 	=	$(shell find srcs -type d)
vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)
 SRCS =     ft_strchr.c    \
        ft_iswhitespace.c    \
        ft_extension.c    \
        ft_isalnum.c    \
        ft_cpy_string.c    \
        ft_merge_space.c    \
        ft_first_word.c    \
        negativ_utils.c    \
        ft_cmp_string.c    \
        ft_strsjoin.c    \
        ft_utils_strs.c    \
        ft_split.c    \
        ft_bzero.c    \
        ft_calloc.c    \
        ft_atoi.c    \
        ft_itoa.c    \
        get_next_line.c    \
        ft_leaks_destroyer.c    \
        ft_handler_destroyer.c    \
        utils_destroyer.c    \
        ft_free.c    \

# $(foreach dir, $(SRC_DIR), $(foreach file, $(wildcard $(dir)/*.c), $(notdir $(file))))

# --  Redirection in OBJS  -- #
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

# --   Compilation flags  -- #
CC= gcc
CFLAGS= -Wall -Werror -Wextra

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

.PHONY: all
all:
	@make $(NAME) --no-print-directory

$(NAME): ${OBJS} $(INC_DIR)/*.h
	@ar -rc ${NAME} $^
	@ranlib ${NAME}
	@echo "$(_GREEN)[100%] LIBFT Compilation Success            $(_ENDL)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@${CC} ${CFLAGS} -o $@ -c $< -I $(INC_DIR)
	@printf "%-60b\r" "$(_GREEN)$(ECHO)$(_CYAN) Compilation $(notdir $@)"

$(OBJ_DIR) :
	@mkdir -p $@

.PHONY: clean
clean:
	@rm -f ${OBJS}
	@rm -rf $(OBJ_DIR)
	@echo "$(_RED)[100%]$(_CYAN)  libft     *.o has been cleaned"

.PHONY: fclean
fclean:
	@rm -f ${NAME}
	@echo "$(_RED)libft.a $(_CYAN)     has been cleaned"

.PHONY: re
re: fclean all
