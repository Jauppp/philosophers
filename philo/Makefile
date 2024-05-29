# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 13:31:53 by cdomet-d          #+#    #+#              #
#    Updated: 2024/05/29 15:15:20 by cdomet-d         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME:= philo
BDIR:= .bdir/
H:= philo.h

CC:= cc
CFLAGS:= -Werror -Wextra -Wall -g3 -I $(H)
DEPFLAGS = -MMD -MP
MAKEFLAGS += --no-print-directory
# INCLUDE:= -lpthread

SRC:= main.c \

OBJ:= $(addprefix $(BDIR), $(SRC:%.c=%.o))
DEPS:= $(OBJ:%.o=%.d)

RM:= rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@printf '$(CB)%.40s\n$(R)' "-- Making $(NAME) ---------------------------------------------------------------------"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(INCLUDE)
	@printf '$(CB)%.40s\n$(R)' "-- All done ! <3 ---------------------------------------------------------------------"

$(BDIR)%.o: $(SRC)%.c $(H)
	@printf '$(CB)%.40s\n$(R)' "-- Creating objects ---------------------------------------------------------------------"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(DEPFLAGS) -o $@ -c $<
	@printf '$(F)%.40s\n$(R)' "creating $@"
	
-include $(DEPS)

clean: 
	@printf '$(CB)%.40s\n$(R)' "-- Deleting $(BDIR) ---------------------------------------------------------------------"
	$(RM) $(BDIR)

fclean: clean
	@printf '$(CB)%.40s\n$(R)' "-- Deleting $(NAME) ---------------------------------------------------------------------"
	$(RM) $(NAME)

re: fclean all

# Text
R=\033[0m
F=\033[2m
U=\033[4m
B=\033[1m

# Codes d'échappement ANSI pour les couleurs
PB=$(PINK)$(BOLD)
MB=$(MAGENTA)$(B)
CB=$(CYAN)$(B)

BGA=$(WHITE)$(BG_B)
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
MAGENTA=\033[0;35m
CYAN=\033[0;36m
WHITE=\033[0;37m
PINK=\033[38;5;206m.

# Codes d'échappement ANSI pour le texte en gras
BOLD=\033[1m

# Codes d'échappement ANSI pour les fonds colorés
BG_RED=\033[41m
BG_GREEN=\033[42m
BG_YELLOW=\033[43m
BG_B=\033[44m
BG_MAGENTA=\033[45m
BG_C=\033[46m
BG_WHITE=\033[47m
