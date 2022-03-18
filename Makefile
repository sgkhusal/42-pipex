# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: coder <coder@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/04 21:14:15 by coder             #+#    #+#              #
#    Updated: 2022/03/14 21:13:36 by coder            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =					pipex
BONUS =					pipex_bonus

# **************************************************************************** #
# MY LIBRARIES - libft.a and libftprintf.a
PRINTF_PATH =	./my_libs/ft_printf/
LIBFT_PATH =	./my_libs/libft/

PRINTF =		$(PRINTF_PATH)libftprintf.a
LIBFT =			$(LIBFT_PATH)libft.a
LIBFT_HEADER =	$(LIBFT_PATH)src/libft.h
# **************************************************************************** #

# INPUTS

SRC_PATH =			./src
OBJ_PATH =			./obj
SRC_BONUS_PATH =	./bonus
OBJ_BONUS_PATH =	./obj/bonus

SRC_FILES =			pipex.c

SRC =				$(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ =				$(SRC:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)

SRC_BONUS_FILES =	

SRC_BONUS =			$(addprefix $(SRC_BONUS_PATH)/, $(SRC_BONUS_FILES))
OBJ_BONUS =			$(SRC_BONUS:$(SRC_BONUS_PATH)/%.c=$(OBJ_BONUS_PATH)/%.o)

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

bonus:	$(BONUS)

$(OBJ_PATH)/%.o:	$(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BONUS_PATH)/%.o:	$(SRC_BONUS_PATH)/%.c
	@mkdir -p $(OBJ_BONUS_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(LIBFT) $(PRINTF) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(PRINTF) $(LIBFT) $(MLXFLAGS)
	@echo "\033[1;32m"
	@echo "************************************"
	@echo "           pipex created"
	@echo "************************************"
	@echo "\033[0m"

$(BONUS):	$(LIBFT) $(PRINTF) $(OBJ_BONUS)
	$(CC) $(CFLAGS) -o $@ $(OBJ_BONUS) $(PRINTF) $(LIBFT) $(MLXFLAGS)
	@echo "\033[1;32m"
	@echo "************************************"
	@echo "        pipex_bonus created"
	@echo "************************************"
	@echo "\033[0m"

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