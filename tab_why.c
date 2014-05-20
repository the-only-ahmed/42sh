/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_why.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 18:30:14 by jyim              #+#    #+#             */
/*   Updated: 2014/03/27 15:29:33 by nsavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		fn_join_why(t_why *e)
{
	while (e->tabl[e->i])
	{
		if ((e->directory = opendir(e->tabl[e->i])) == NULL)
		{
			e->tabl = decale_tab(e->tabl, e->i);
			e->i--;
		}
		else
		{
			if (e->tabl[e->i][ft_strlen(e->tabl[e->i]) - 1] != '/')
				e->tabl[e->i] = ft_strjoin(e->tabl[e->i], "/");
			if (e->ch[0])
				e->ch = ft_strjoin(e->ch, " ");
			e->ch = ft_strjoin(e->ch,
						find_match(e->directory, e->pattern, e->tabl[e->i], 1));
		}
		e->i++;
	}
}

char			**fill_tab_why(char *word)
{
	t_why		e;

	e.tabl = NULL;
	if (!ft_strchr(word, '/') || word[0] != '.')
		word = ft_strjoin("./", word);
	while (ft_strchr(word, '/'))
	{
		e.path = pathing(word, &(e.i));
		word = ft_strsub(word, e.i + 1, ft_strlen(word));
		e.x = why_chr(word);
		e.pattern = ft_strsub(word, 0, e.x);
		if (!e.tabl)
		{
			e.tabl = (char**)malloc(sizeof(char*) * 2);
			e.tabl[0] = e.path;
			e.tabl[1] = NULL;
		}
		e.i = 0;
		e.ch = ft_strnew(0);
		fn_join_why(&e);
		free_tab(&(e.tabl));
		e.tabl = ft_strsplit_spaces(e.ch, ' ', 0);
		ft_strdel(&(e.ch));
	}
	return (e.tabl);
}
