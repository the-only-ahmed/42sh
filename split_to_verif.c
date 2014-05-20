/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_verif.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/05 07:10:09 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 19:12:36 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*ltv_return(int i, char **tab, char *line)
{
	ft_strdel(&line);
	i = 0;
	line = ft_strnew(0);
	while (tab[i])
	{
		line = ft_strjoin(line, tab[i]);
		i++;
	}
	free_tab(&tab);
	return (line);
}

static int		fn_loop(char *line, char c, char d)
{
	int		i;
	int		j;
	int		bol;

	i = 0;
	while (line[i])
	{
		if (line[i] == c)
		{
			bol = 0;
			j = i + 1;
			while (line[j] != d)
			{
				if (line[j] != ' ')
					bol = 1;
				j++;
			}
			if (!bol)
				break ;
		}
		i++;
	}
	return (bol);
}

static int		function(char *line, char c, char d)
{
	int		bol;

	bol = fn_loop(line, c, d);
	if (!bol)
	{
		if (c != d)
			ft_printf("42sh: syntax error near unexpected token `)'\n");
		else if (c == '\'' || c == '"')
			ft_printf(": command not found\n");
		return (0);
	}
	return (1);
}

static char		*is_tab(char *line, int *i)
{
	if (line)
	{
		if (ft_strchr(line, '(') && !function(line, '(', ')'))
		{
			*i = -1;
			return (line);
		}
		else if (ft_strchr(line, '`') && !function(line, '`', '`'))
			line = decale_word2(line, '`');
		else if (ft_strchr(line, '"') && !function(line, '"', '"'))
			line = decale_word2(line, '"');
		else if (ft_strchr(line, '\'') && !function(line, '\'', '\''))
			line = decale_word2(line, '\'');
	}
	else
		return (NULL);
	return (line);
}

char			*line_to_verif(char *line)
{
	t_ltverif	v;

	v.i = -1;
	v.tabl = ft_strsplit_mult(line);
	while (v.tabl[++v.i])
	{
		v.q = 0;
		v.qt = 0;
		v.j = -1;
		v.tabl[v.i] = ft_quote(v.tabl[v.i]);
		if (!(v.tabl[v.i] = is_tab(v.tabl[v.i], &(v.i))))
			continue ;
		if (v.i < 0)
			return (NULL);
		while (v.tabl[v.i][++v.j])
		{
			v.q = verif_token(v.tabl[v.i][v.j], v.q, &(v.qt));
			if (ltv(v))
			{
				v.tabl[v.i] = decale_word(v.tabl[v.i], v.j);
				v.j--;
			}
		}
	}
	return (ltv_return(v.i, v.tabl, line));
}
