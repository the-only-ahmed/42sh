/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsavry <nsavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 14:29:17 by nsavry            #+#    #+#             */
/*   Updated: 2014/03/27 15:53:15 by nsavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		left_if(t_tree **tree)
{
	return (((*tree)->father && (!ft_strcmp((*tree)->father->cmd, ">") ||\
	!ft_strcmp((*tree)->father->cmd, ">>")) && !(*tree)->father->done));
}

int		left_else(t_tree **tree)
{
	return (((*tree)->father && !ft_strcmp((*tree)->father->cmd, "|") &&\
	!(*tree)->father->done));
}

int		pipe_right_chd(t_tree **right)
{
	return (((*right)->father->father &&\
	(!ft_strcmp((*right)->father->father->cmd, ">") ||\
	!ft_strcmp((*right)->father->father->cmd, ">>"))));
}

int		special_split(t_spec s, char *str)
{
	return ((((s.i && str[s.i - 1] != '\\') ||\
	(!s.i)) && (str[s.i] == '"' ||\
	str[s.i] == '\'' || str[s.i] == '`')));
}

int		split_spaces(t_dlspaces s, const char *str, char c)
{
	return ((str[s.i + s.cnt] && (s.q || str[s.i + s.cnt] != c ||\
	(str[s.i + s.cnt - 1] && \
	str[s.i + s.cnt - 1] == '\\' && \
	str[s.i + s.cnt] == c))));
}
