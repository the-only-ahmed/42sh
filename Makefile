# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/25 02:16:49 by jyim              #+#    #+#              #
#    Updated: 2014/03/27 16:32:24 by ael-kadh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

SRC = ft_strsplit_spec.c test.c deletion.c main.c ft_env.c ft_path.c ft_cmd.c\
		ft_cd.c fn_pwd.c free.c work.c last_visit.c occurence.c quotes.c\
		parantheses.c echo.c fuck.c pipe.c error.c priority.c printing.c\
		missing_cmd.c chevron.c realloc.c split_to_verif.c ft_env2.c bin_op.c\
		the_quotes.c backslash.c sous_shell.c ft_arrow.c ft_ctrl_key.c\
		ft_current.c ft_other_key.c ft_signal.c ft_tab_ptr.c ft_termcaps.c\
		match.c ft_history.c mat_why.c exec.c bk_qotes.c tri_tab.c ft_cd2.c\
		split_spaces.c printing2.c decale.c tree_parser.c chevron2.c\
		ft_strsplit_spec2.c pipe2.c export.c others.c others2.c tab_why.c\
		instance.c vars.c completion.c director.c finder.c dollar.c\
		completion_finder.c ft_strisint.c colors.c term_caps.c\
		ft_term_resize.c define_one.c define_two.c define_three.c

OBJ = $(SRC:.c=.o)

FLAGS = -g3 -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@cc $(OBJ) -L libft -lft -ltermcap libft/printf/libftprintf.a -o $(NAME)

%.o: %.c
	@cc $(FLAGS) -c -I libft/ -I libft/printf/includes $<

clean:
	@/bin/rm $(OBJ)
	@make -C libft/ clean

fclean:
	@/bin/rm -f $(OBJ)
	@/bin/rm -f $(NAME)
	@make -C libft/ fclean

re: fclean all
