/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 14:51:13 by nsavry            #+#    #+#             */
/*   Updated: 2014/03/27 16:42:24 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		split_sp_tok(t_dlspaces s, const char *str, char c)
{
	return (str[s.i] && !s.q && str[s.i] == c && back_line((char *)str, s.i));
}

int		delete_spaces_2(t_spaces s, char *str)
{
	return ((!s.q && ((str[s.i] == ' ' &&
	(s.i == 0 || s.i == (int)ft_strlen(str) - 1)) ||\
	(str[s.i] == ' ' && str[s.i + 1] == ' '))));
}

int		work_chd(t_tree **tree)
{
	return (((*tree)->father && (!ft_strcmp((*tree)->father->cmd, ">") ||\
	!ft_strcmp((*tree)->father->cmd, ">>")) && !(*tree)->done));
}

int		work_chl(t_tree **tree)
{
	return (((*tree)->father && (!ft_strcmp((*tree)->father->cmd, "<") ||\
	!ft_strcmp((*tree)->father->cmd, "<<")) && !(*tree)->done));
}

int		the_work(t_tree *tree)
{
	return ((!tree->bol &&\
	((tree->father && ft_strcmp(tree->father->cmd, THE_CREED)) ||\
	!tree->father)));
}
