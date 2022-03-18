# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: coder <coder@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/04 21:14:15 by coder             #+#    #+#              #
#    Updated: 2022/03/14 21:26:18 by coder            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =					error

# **************************************************************************** #
# MY LIBRARIES - libft.a and libftprintf.a
PRINTF_PATH =	../my_libs/ft_printf/
LIBFT_PATH =	../my_libs/libft/

PRINTF =		$(PRINTF_PATH)libftprintf.a
LIBFT =			$(LIBFT_PATH)libft.a
LIBFT_HEADER =	$(LIBFT_PATH)src/libft.h
# **************************************************************************** #

# INPUTS

SRC =			errno.c

OBJ =				$(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)

# **************************************************************************** #

# compilation
CC =		gcc
CFLAGS =	-Wall -Werror -Wextra #-fsanitize=leak
GNLFLAGS =	-D BUFFER_SIZE=10

# clean
RM =		-rm -f
RM_DIR =	rm -rf

# **************************************************************************** #
# rules

all:	$(NAME)

$(OBJ_PATH)/%.o:	$(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(LIBFT) $(PRINTF) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(PRINTF) $(LIBFT) $(MLXFLAGS)

$(LIBFT):
	cd $(LIBFT_PATH) && $(MAKE)
	@echo "libft.a created"

$(PRINTF):
	cd $(PRINTF_PATH) && $(MAKE)
	@echo "libftprintf.a created"

clean:
		@$(RM_DIR) $(OBJ_PATH)

fclean:		clean
		@$(RM) $(NAME)
		@$(RM) $(BONUS)

re:			fclean all

reb:		fclean bonus

reall:		fcleanlib re

cleanlib:	
	@cd $(PRINTF_PATH) && $(MAKE) clean
	@cd $(LIBFT_PATH) && $(MAKE) clean

fcleanlib:
	@cd $(PRINTF_PATH) && $(MAKE) fclean
	@cd $(LIBFT_PATH) && $(MAKE) fclean

.PHONY: all clean fclean re
