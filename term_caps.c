/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_caps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 11:56:01 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 13:57:29 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*term_cp(t_term *term)
{
	int		ret;

	while ((ret = read(0, term->buf, 10000)) > 4)
	{
		ft_putstr(term->buf);
		g_glob.str = ft_strinjoin(g_glob.str, term->buf, g_glob.i);
		g_glob.i += ft_strlen(term->buf) - 1;
		ft_bzero(term->buf, 10000);
	}
	if (ret == -1)
	{
		ft_bzero(term->buf, 4);
		ft_strdel(&(g_glob.str));
		g_glob.str = ft_strnew(0);
		term->buf = ft_strnew(4);
		term->buf[0] = 10;
	}
	return (term->buf);
}

static void		*term_fill(int prompt)
{
	t_term		*term;

	ft_term_resize(0);
	term = malloc(sizeof(t_term));
	term->tmp = malloc(sizeof(char));
	term->buf = malloc(sizeof(char) * 10000);
	term->prompt = prompt;
	ft_signal();
	g_glob.str = malloc(sizeof(char) * 2);
	g_glob.str[0] = 0;
	g_glob.i = 0;
	g_glob.j = 0;
	return (term);
}

char			*ft_termcaps(int prompt)
{
	void	(*ft_back)(t_term *term);
	t_term	*term;

	term = term_fill(prompt);
	while (42)
	{
		term->buf = term_cp(term);
		if (term->buf[0] == 10)
		{
			ft_add_history(g_glob.str);
			g_glob.nb = 50;
			write(1, "\n", 1);
			return (g_glob.str);
		}
		else
		{
			ft_back = ft_seek(term->buf, term);
			(*ft_back)(term);
		}
		ft_bzero(term->buf, 10000);
	}
	return (NULL);
}
