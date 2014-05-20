/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/01 12:56:37 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/25 21:28:18 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		priority(char *str)
{
	if (!ft_strcmp(str, ";;"))
		return (5);
	else if (!ft_strcmp(str, ";") || !ft_strcmp("&", str))
		return (4);
	else if (!ft_strcmp(str, "||") || !ft_strcmp("&&", str))
		return (3);
	else if (!ft_strcmp(str, "<") || !ft_strcmp(str, ">") ||
				!ft_strcmp(str, "|") || !ft_strcmp(str, "<<") ||
				!ft_strcmp(str, ">>") || !ft_strcmp(str, ">|") ||
				!ft_strcmp(str, THE_CREED))
		return (2);
	else if (!ft_strcmp("{", str) || !ft_strcmp(str, "}"))
		return (1);
	else
		return (0);
}

int		high_prio_pos(char **tab, int p)
{
	int		i;
	int		pos;
	int		bol;

	bol = -1;
	i = 0;
	pos = 0;
	while (tab[i] && (i < p || p == -1))
	{
		if (priority(tab[i]) >= bol)
		{
			bol = priority(tab[i]);
			pos = i;
		}
		i++;
	}
	return (pos);
}

int		high_prio(char **tab, int p)
{
	int		i;
	int		bol;

	bol = -1;
	i = 0;
	while (tab[i] && (i < p || p == -1))
	{
		if (priority(tab[i]) >= bol)
			bol = priority(tab[i]);
		i++;
	}
	return (bol);
}

int		occ_prio(char **tab, int p)
{
	int		i;
	int		nb;

	nb = 0;
	i = 0;
	while (tab[i])
	{
		if (priority(tab[i]) == p)
			nb++;
		i++;
	}
	return (nb);
}
