/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 19:24:42 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 19:14:45 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		deserve(char *str)
{
	int		i;
	int		q;
	char	qt;

	i = 0;
	q = 0;
	qt = 0;
	while (str[i])
	{
		if (back_line(str, i) &&
		(str[i] == '"' || str[i] == '\'' || str[i] == '`'))
		{
			if (!q)
				qt = str[i];
			if (qt == str[i])
				q = (q) ? 0 : 1;
		}
		i++;
	}
	if (q)
		return (qt);
	return (0);
}

char		*ft_quote(char *line)
{
	char		*str;

	str = NULL;
	line = delete_spaces(line);
	if (line[ft_strlen(line) - 1] == '\\' &&
			((((int)ft_strlen(line) - 2) >= 0 &&
				line[ft_strlen(line) - 2] != '\\') || (ft_strlen(line) == 1)))
	{
		while (line[ft_strlen(line) - 1] == '\\' && ((ft_strlen(line) == 1) ||
						(((int)ft_strlen(line) - 2) >= 0 &&
									line[ft_strlen(line) - 2] != '\\')))
		{
			line = fn_delete(line, ft_strlen(line) - 1);
			str = ft_termcaps(ft_printf("> "));
			line = ft_strjoin(line, str);
		}
	}
	if (ft_strchr(line, '"') || ft_strchr(line, '\'') || ft_strchr(line, '`'))
		line = the_quotes(line);
	line = ft_parentheses(line, str);
	return (line);
}
