# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkallio <lkallio@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/15 12:30:26 by lkallio           #+#    #+#              #
#    Updated: 2020/02/12 08:59:30 by lkallio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRC = dbl_data.c ft_printf.c handle_double.c handle_ints.c handle_n_str.c pf_utils.c write_double.c write_ints.c
SRCDIR = src/
OBJ = $(SRC:.c=.o)
OBJDIR = obj/
INC = includes/
FLAGS = -Wall -Wextra -Werror

SETCYAN = \033[1;36m
UNSETCOLOR = \033[0m

.PHONY: all clean fclean re notify

all: $(NAME)

notify:
	@printf "$(SETCYAN)Updating object files...$(UNSETCOLOR)\n"

$(OBJDIR)%.o: $(SRCDIR)%.c | notify
	@gcc $(FLAGS) -c $< -I $(INC) -o $@

$(NAME): $(addprefix $(OBJDIR), $(OBJ))
	ar rcs $(NAME) $?

clean:
	rm -rf $(addprefix $(OBJDIR), $(OBJ))

fclean: clean
	rm -rf $(NAME)

re: fclean all
