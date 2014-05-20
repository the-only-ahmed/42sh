/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/25 16:05:09 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 15:42:48 by nsavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		fill_del(t_spaces *s)
{
	s->i = 0;
	s->q = 0;
	s->qt = 0;
}

char			*delete_spaces(char *str)
{
	t_spaces		s;

	fill_del(&s);
	if (!str)
		return ("");
	while (str[s.i])
	{
		s.q = verif_token(str[s.i], s.q, &(s.qt));
		if (delete_spaces_2(s, str))
		{
			s.j = s.i;
			while (str[s.j] != '\0')
			{
				str[s.j] = str[s.j + 1];
				if (str[s.j] == '\t')
					str[s.j] = ' ';
				s.j++;
			}
			s.i--;
		}
		s.i++;
	}
	return (str);
}

char			*delete_chars(char *str, char c)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == ' ' && i == 0) || (str[i] == c && str[i + 1] == c))
		{
			j = i;
			while (str[j] != '\0')
			{
				str[j] = str[j + 1];
				j++;
			}
			i--;
		}
		i++;
	}
	return (str);
}

char			*fn_delete(char *str, int i)
{
	int		length;

	length = ft_strlen(str);
	while (i < length)
	{
		str[i] = str[i + 1];
		i++;
	}
	return (str);
}

char			*fn_delete_word(char *str, int i, int length)
{
	if (length < 0)
		return (str);
	while (length)
	{
		str = fn_delete(str, i);
		length--;
	}
	return (str);
}
