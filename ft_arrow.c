/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 05:13:32 by nsavry            #+#    #+#             */
/*   Updated: 2014/03/27 14:09:31 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_larrow(t_term *term)
{
	int		i;

	i = 0;
	if (g_glob.i != 0 && (g_glob.i + (term->prompt / 2)) < g_glob.c_max - 1)
	{
		ft_putstr_fd(term->buf, 1);
		g_glob.i--;
	}
	(void)term;
}

void	ft_rarrow(t_term *term)
{
	if (g_glob.str[g_glob.i] != 0)
	{
		ft_putstr_fd(term->buf, 1);
		g_glob.i++;
	}
}

void	ft_uarrow(t_term *term)
{
	(void)term;
	if (g_glob.nb == 0 || g_glob.array[g_glob.nb - 1] == NULL)
		return ;
	while (g_glob.i != 0)
	{
		write(1, "\b", 1);
		ft_trans("dm");
		ft_trans("dc");
		ft_trans("ed");
		g_glob.i--;
	}
	ft_trans("cd");
	ft_history_up();
}

void	ft_darrow(t_term *term)
{
	(void)term;
	if (g_glob.nb == 50)
		return ;
	while (g_glob.i != 0)
	{
		write(1, "\b", 1);
		ft_trans("dm");
		ft_trans("dc");
		ft_trans("ed");
		g_glob.i--;
	}
	ft_trans("cd");
	ft_history_down();
}
