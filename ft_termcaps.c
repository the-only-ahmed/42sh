/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcaps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/05 19:58:15 by nsavry            #+#    #+#             */
/*   Updated: 2014/03/27 17:07:17 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <stdlib.h>
#include "shell.h"

void		ft_get_term(void)
{
	char	*termtype;
	char	*term_buffer;
	char	**env;

	env = get_env(NULL);
	termtype = &env[search_exp("TERM", env)][5];
	term_buffer = (char*)malloc(sizeof(char) * 9999);
	tgetent(term_buffer, termtype);
}

void		ft_init_term(int sig_number)
{
	struct termios				tattr;
	static struct termios		*temp = NULL;

	sig_number = 0;
	ft_get_term();
	tcgetattr(0, &tattr);
	temp = malloc(sizeof(struct termios));
	*temp = tattr;
	tattr.c_lflag &= ~(ECHO | ICANON);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &tattr);
	ft_trans("im");
}

char		*ft_trans(char *str)
{
	char	*ch;

	ch = tgetstr(str, NULL);
	if (ch)
		ft_printf("%s", ch);
	return (ch);
}

void		ft_def_term(int i)
{
	struct termios	tattr;

	i = 0;
	ft_trans("ei");
	tcgetattr(0, &tattr);
	tattr.c_lflag |= (ECHO | ICANON);
	tcsetattr(0, TCSANOW, &tattr);
	return ;
}
