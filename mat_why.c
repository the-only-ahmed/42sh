/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_why.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 01:45:59 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/23 01:16:39 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			*ft_all_strjoin(char **tab)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strnew(0);
	while (tab[i])
	{
		str = ft_strjoin(str, tab[i]);
		i++;
		if (tab[i])
			str = ft_strjoin(str, " ");
	}
	return (str);
}

static char		**make_tab(char **tab, char *pattern)
{
	int				i;
	unsigned int	len;

	i = 0;
	len = ft_strlen(pattern);
	if (ft_strncmp(pattern, "./", 2) == 0)
		len -= 2;
	while (tab[i])
	{
		if (ft_strlen(tab[i]) != len)
		{
			decale_tab(tab, i);
			i--;
		}
		i++;
	}
	return (tab);
}

void			fill_tmp(char *word, t_tmp *e, int bol)
{
	if (!bol)
	{
		e->i = 0;
		e->i2 = 0;
		e->b = 0;
		e->len = ft_strlen(word);
		e->tmp = (char **)malloc(sizeof(char *) * (ft_strlen(word) + 1));
	}
	else
	{
		if (e->b != e->i)
			e->tmp[e->i2++] = ft_strsub(word, e->b, ft_strlen(word));
		e->tmp[e->i2] = NULL;
	}
}

static char		**make_tmp(char *word)
{
	t_tmp		e;

	fill_tmp(word, &e, 0);
	while (word[e.i])
	{
		if (word[e.i] == '?')
		{
			e.j = e.i;
			while (e.j >= 0 && word[e.j] != ' ' && word[e.j] != '\t')
				e.j--;
			e.j++;
			if (e.j - e.b)
				e.tmp[e.i2++] = ft_strsub(word, e.b, e.j - e.b - 1);
			find_word(&word[e.j], &(e.ch), '?');
			e.i += ft_strlen(e.ch) - (e.i - e.j);
			e.b = e.i + 1;
			e.tmp[e.i2++] = ft_strdup(e.ch);
			ft_strdel(&(e.ch));
		}
		e.i++;
		if (e.i > e.len)
			break ;
	}
	fill_tmp(word, &e, 1);
	return (e.tmp);
}

char			*match_compare(char *word)
{
	t_cmp		e;

	e.i = -1;
	e.g = ft_strnew(0);
	e.loop = make_tmp(word);
	while (e.loop[++e.i])
	{
		if (!(ft_strchr(e.loop[e.i], '?')))
		{
			e.g = ft_strjoin(e.g, e.loop[e.i]);
			if (e.loop[e.i + 1])
				e.g = ft_strjoin(e.g, " ");
		}
		else
		{
			e.tabl = fill_tab_why(e.loop[e.i]);
			e.tabl = make_tab(e.tabl, e.loop[e.i]);
			e.tmp = ft_all_strjoin(e.tabl);
			e.g = ft_strjoin(e.g, " ");
			e.g = ft_strjoin(e.g, e.tmp);
			free_tab(&(e.tabl));
		}
	}
	return (e.g);
}
