/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 05:17:09 by nsavry            #+#    #+#             */
/*   Updated: 2014/03/27 14:20:12 by nsavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "shell.h"

void	ft_delete(t_term *term)
{
	if (g_glob.i > 0)
	{
		ft_strdel(&(term->tmp));
		term->tmp = ft_strdup(g_glob.str + g_glob.i);
		g_glob.str[g_glob.i - 1] = 0;
		g_glob.str = ft_strjoin(g_glob.str, term->tmp);
		g_glob.i--;
		write(1, "\b", 1);
		ft_trans("dm");
		ft_trans("dc");
		ft_trans("ed");
	}
}

void	ft_other(t_term *term)
{
	if (ft_strncmp("\033[3~", term->buf, 4) == 0)
	{
		term->buf[0] = '~';
		write(1, "~", 1);
	}
	else
		ft_putchar_fd(term->buf[0], 1);
	ft_strdel(&(term->tmp));
	ft_bzero(term->tmp, 0);
	term->tmp = ft_strdup(g_glob.str + g_glob.i);
	g_glob.str[g_glob.i] = term->buf[0];
	g_glob.str[g_glob.i + 1] = 0;
	g_glob.str = ft_strjoin(g_glob.str, term->tmp);
	g_glob.i++;
}

int		ft_return(char **str, char **buf)
{
	ft_putchar('\n');
	ft_putstr(*str);
	ft_putchar('$');
	(*str)[0] = 0;
	write(1, buf[0], 1);
	return (0);
}
