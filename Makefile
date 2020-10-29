#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwagner <cwagner@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/25 12:34:27 by cwagner           #+#    #+#              #
#    Updated: 2014/03/27 20:37:24 by cwagner          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = 		42sh

DEBUG=		yes

ifeq ($(DEBUG), no)
	CC = clang
	CFLAGS=-Wall -Wextra -Werror -pedantic -g3
else
	CC = gcc
	CFLAGS=-Wall -Wextra -Werror
endif

INCLUDES = 	-I includes/

SRCS =		srcs/
LIB = 		libft/

TCDIR = 	$(SRCS)termcaps/
TCFILES =	shell_changes.c			\
			ft_read_input.c			\
			ft_key_action_1.c		\
			ft_key_action_2.c		\
			ft_key_action_3.c		\
			ft_key_action_4.c		\
			ft_key_action_5.c		\
			ft_cmd_history.c		\
			print_funcs_1.c			\
			print_funcs_2.c			\
			signals.c				\
			signal_handle.c			\
			signal_handle2.c		\
			get_line.c				\
			termios.c
TC =		$(addprefix $(TCDIR), $(TCFILES))

BIDIR =		$(SRCS)builtins/
BIFILES =	builtins.c				\
			builtins_extra.c		\
			builtins_bonus.c		\
			builtins_bonus_extra.c	\
			builtins_tools.c		\
			bi_cd.c					\
			bi_cd2.c				\
			builtin_echo_1.c		\
			builtin_echo_2.c		\
			bi_history_1.c			\
			bi_hash.c				\
			bi_hash2.c				\
			bi_setenv.c
BI =		$(addprefix $(BIDIR), $(BIFILES))

TLDIR =		$(SRCS)tools/
TLFILES =	tools.c
TL =		$(addprefix $(TLDIR), $(TLFILES))

PMDIR =		$(SRCS)parameters/
PMFILES =	infos.c
PM		=	$(addprefix $(PMDIR), $(PMFILES))

ENVDIR =	$(SRCS)env/
ENVFILES =	env_tools1.c			\
			env_tools2.c
ENV =		$(addprefix $(ENVDIR), $(ENVFILES))

LEXDIR =	$(SRCS)lexer/
LEXFILES =	lexing.c				\
			lstlex.c				\
			checktoken.c			\
			checktoken_2.c

LEX =		$(addprefix $(LEXDIR), $(LEXFILES))

PARDIR =	$(SRCS)parser/
PARFILES =	parsing.c				\
			check1.c				\
			check2.c				\
			check3.c

PAR =		$(addprefix $(PARDIR), $(PARFILES))

CMDDIR =	$(SRCS)cmd/
CMDFILES =	cmd_execute.c\
			hash.c\
			dotree.c\
			noredir.c\
			redir1.c\
			redir2.c\
			redir3.c
CMD =		$(addprefix $(CMDDIR), $(CMDFILES))

MAIN = 		$(SRCS)main.c $(SRCS)error.c $(SRCS)print.c $(SRCS)free.c

ALL = 		$(MAIN) $(TC) $(ENV) $(BI) $(PM) $(CMD) $(LEX) $(PAR) $(TL)

OBJ = 		$(ALL:.c=.o)

all: $(NAME)

ifeq ($(DEBUG), no)
	@echo
	@echo "\033[33m[Generation]\033[0m mode debug"
	@echo
else
	@echo
	@echo "\033[33m[Generation]\033[0m Mode: \033[32m[Release]\033[0m"
	@echo
endif

$(NAME): $(OBJ)	
	@echo "\033[31m[Libft] \033[0m" | tr -d '\n'
	make -C $(LIB)
	@echo "\033[32m[Building] \033[0m" | tr -d '\n'
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJ) -L $(LIB) -lft -ltermcap

remake:
	@echo "\033[31m[Re-Libft] \033[0m" | tr -d '\n'
	make re -C $(LIB)

%.o: %.c
	@echo "\033[33m[Doing object] \033[0m" | tr -d '\n'
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	@echo "\033[34m[Cleaning] \033[0m" | tr -d '\n'
	rm -f $(OBJ)

fclean: clean
	@echo "\033[34m[Filecleaning] \033[0m" | tr -d '\n'
	rm -f $(NAME)

ffclean: fclean
	make fclean -C $(LIB)

re: fclean all

rre: remake re

run: all
	@echo "\033[32m[Running Binary]\033[0m" | tr -d '\n'
	@echo ""
	@./$(NAME)
	@make clean

debug: re
	gdb ./$(NAME)

.PHONY: clean fclean re
