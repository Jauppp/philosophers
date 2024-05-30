# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/28 13:31:53 by cdomet-d          #+#    #+#              #
#    Updated: 2024/05/30 17:52:03 by cdomet-d         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME:= philo
BDIR:= .bdir/
H:= philo.h

CC := cc
CFLAGS := -Werror -Wextra -Wall -g3 
CPPFLAGS := -I . -MMD -MP
MAKEFLAGS += --no-print-directory
S_DIR= src/

SRCS+= $(addprefix $(S_DIR), $(M_SRC))
M_SRC:=	main.c \
		init_philo.c \
		routine.c \

SRCS+= $(addprefix $(S_DIR)$(U_SUBDIR), $(U_SRC))
U_SUBDIR:= utils/
U_SRC:=	display.c \
		error_management.c \
		ft_atoi.c \

OBJS := $(patsubst $(S_DIR)%.c,$(BDIR)%.o,$(SRCS))
DEPS := $(OBJS:%.o=%.d)

RM := rm -rf

all: $(NAME)
bonus : $(BONUS)

$(NAME): $(OBJS)
	@echo
	@printf '$(CB)%.40s\n\n$(R)' "-- Making $(NAME)... ---------------------------------------------------------------------"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo

$(BDIR)%.o: $(S_DIR)%.c $(H)
	@mkdir -p $(dir $@)
	@echo "$@"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

 -include $(DEPS)

clean:
	@echo
	@printf '$(CB)%.40s\n$(R)' "-- Cleaning... ---------------------------------------------------------------------"
	$(RM) $(BDIR)

	
fclean: clean
	$(RM) $(NAME)
	@echo
	
re: fclean all

VPARAM:= valgrind --leak-check=full --track-origin=yes --tool=helgrind
run: all
	$(VPARAM) ./$(NAME)

help:
	@echo "make \t\t $(FAINT)creates the executable$(R)"
	@echo "make bonus \t $(FAINT)creates the bonus executable$(R)"
	@echo "make clean \t $(FAINT)deletes object files & dependencies$(R)"
	@echo "make fclean \t $(FAINT)deletes everything the makefile created$(R)"
	@echo "make kitty \t $(FAINT)prints a lil kitty on the terminal$(R)"
	@echo "make re \t $(FAINT)deletes all objects & dependencies and recompiles the executable$(R)"
	@echo "make re_bonus \t $(FAINT)deletes all objects & dependencies and recompiles the bonus$(R)"

kitty:
	@echo "   |\__/,|   ( \  "
	@echo " _.|o o  |_   ) ) "
	@echo "-(((---(((--------"


.PHONY : clean fclean all re help run kitty

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
