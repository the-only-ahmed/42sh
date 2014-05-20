/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/11 01:56:08 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 13:52:38 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*the_quotes(char *line)
{
	char	c;
	int		len;
	char	*str;

	c = deserve(line);
	if (c)
	{
		if (c == '\'')
			len = ft_printf("quote> ");
		else if (c == '"')
			len = ft_printf("dquote> ");
		else
			len = ft_printf("bquote> ");
		str = ft_termcaps(len);
		line = ft_strjoin(line, str);
		line = the_quotes(line);
	}
	return (line);
}

int		verif_token(char c, int q, char *qt)
{
	if (c == '"' || c == '\'' || c == '`')
	{
		if (!q)
			*qt = c;
		if (*qt == c)
			q = (q) ? 0 : 1;
	}
	return (q);
}

char	*del_quotes(char *str)
{
	t_delqt		e;

	e.i = 0;
	e.a = 0;
	e.q = 0;
	e.qt = 0;
	while (str[e.i])
	{
		if (str[e.i] == '\\' && str[e.i + 1] != ' ')
		{
			str = decale_word(str, e.i);
			e.i++;
			continue ;
		}
		e.q = verif_token(str[e.i], e.q, &(e.qt));
		if (e.a != e.q)
		{
			e.a = e.q;
			str = decale_word(str, e.i);
			e.i--;
		}
		e.i++;
	}
	return (str);
}
