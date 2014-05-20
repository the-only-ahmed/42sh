/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/09/21 00:33:11 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 15:57:13 by nsavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				match(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		while (match_2(s1, s2))
			s1++;
		while ((*s1 == *s2 || (*s2 == '?' && *(s2 - 1) != '\\')) && *s2 != '\0')
		{
			s1++;
			s2++;
		}
		if (*s2 == '*' && *(s2 - 1) != '\\')
		{
			s2++;
			s1--;
		}
		else if ((*s1 != *s2 && *s2 != '?') && *(s2 - 1) != '*')
			return (0);
		s1++;
	}
	if (*s2 == '\0' || (s1[0] == '\0' && *s2 == '*' && *s2 != '\\'))
		return (1);
	return (0);
}

static char		**make_tmp(char *word)
{
	t_tmp		e;

	fill_tmp(word, &e, 0);
	while (word[e.i])
	{
		if (word[e.i] == '*')
		{
			e.j = e.i;
			while (e.j >= 0 && word[e.j] != ' ' && word[e.j] != '\t')
				e.j--;
			e.j++;
			if (e.j - e.b)
				e.tmp[e.i2++] = ft_strsub(word, e.b, e.j - e.b - 1);
			find_word(&word[e.j], &(e.ch), '*');
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

char			*the_star(char *word)
{
	t_cmp		e;

	e.i = -1;
	e.g = ft_strnew(0);
	e.loop = make_tmp(word);
	while (e.loop[++e.i])
	{
		if (!(ft_strchr(e.loop[e.i], '*')))
		{
			e.g = ft_strjoin(e.g, e.loop[e.i]);
			if (e.loop[e.i + 1])
				e.g = ft_strjoin(e.g, " ");
		}
		else
		{
			e.tabl = fill_tab_why(e.loop[e.i]);
			e.tmp = ft_all_strjoin(e.tabl);
			e.g = ft_strjoin(e.g, " ");
			e.g = ft_strjoin(e.g, e.tmp);
			free_tab(&(e.tabl));
		}
	}
	return (e.g);
}
