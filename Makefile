# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/04 13:09:35 by lkallio           #+#    #+#              #
#    Updated: 2021/04/27 19:25:38 by lkallio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRC =  pf_dbl_data.c pf_ft_printf.c pf_handle_buffer.c pf_handle_double.c \
		pf_handle_ints.c pf_handle_n_str.c pf_utils.c pf_write_double.c pf_write_ints.c
FLAGS = -Wall -Wextra -Werror
SRCDIR = src/
OBJ = $(SRC:.c=.o)
OBJDIR = obj/
INC = includes

.PHONY: all clean fclean re notify

all: $(NAME)

notify:
	@[ -d obj ] || mkdir obj

$(OBJDIR)%.o: $(SRCDIR)%.c | notify
	@[ -d obj ] || mkdir obj
	@gcc $(FLAGS) -c $< -I $(INC) -o $@

$(NAME): $(addprefix $(OBJDIR), $(OBJ))
	@ar rcs $(NAME) $?

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
