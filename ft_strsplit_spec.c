/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_spec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 04:12:09 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 16:56:39 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		verif(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&' || c == ';')
		return (1);
	return (0);
}

char			*ft_cmdup(int deb, char *str, int fin)
{
	char	*cpy;
	int		i;

	i = 0;
	cpy = (char*)malloc(sizeof(char) * (fin - deb + 1));
	while (deb <= fin)
	{
		cpy[i] = str[deb];
		i++;
		deb++;
	}
	cpy[i] = '\0';
	return (cpy);
}

static void		fill_spec(t_spec *s, char *str)
{
	s->i = 0;
	s->j = 0;
	s->word = 0;
	s->qt = 0;
	s->q = 0;
	s->p = 0;
	s->tabl = (char **)malloc(sizeof(char *) * ft_strlen(str));
}

static void		ft_spec2(t_spec *s, char *str)
{
	if (s->i)
		s->tabl[s->word] = delete_spaces(ft_cmdup(s->j, str, s->i - 1));
	else
		s->word--;
	s->tabl[s->word + 1] = ft_strdup(fn_put(str, &(s->i)));
	s->word += 2;
	s->j = s->i + 1;
}

char			**ft_strsplit_spec(char *str)
{
	t_spec		s;

	fill_spec(&s, str);
	while (str[s.i])
	{
		if (special_split(s, str))
		{
			if (!s.q)
				s.qt = str[s.i];
			if (s.qt == str[s.i])
				s.q = (s.q) ? 0 : 1;
		}
		if (str[s.i] == '(' && back_line(str, s.i))
			s.p++;
		if (str[s.i] == ')' && back_line(str, s.i))
			s.p--;
		if (verif(str[s.i]) && !s.q && !s.p)
			ft_spec2(&s, str);
		s.i++;
	}
	if (s.i > s.j)
		s.tabl[s.word++] = delete_spaces(ft_cmdup(s.j, str, s.i - 1));
	s.tabl[s.word] = NULL;
	return (s.tabl);
}
