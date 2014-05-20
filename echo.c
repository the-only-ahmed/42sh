/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 04:01:33 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 16:55:27 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		new_line(char *str, int i, int *nl)
{
	if (str[i] == '-' && str[i + 1] && str[i + 1] == 'n')
	{
		i += 2;
		*nl = 0;
	}
	if (str[i] == 'c' && !back_line(str, i))
	{
		i += 2;
		*nl = 0;
	}
	else if (str[i] == 'n' && !back_line(str, i))
	{
		i += 2;
		ft_putchar('\n');
	}
	return (i);
}

static int		the_echo(char *str, int nl)
{
	int		i;
	int		b;
	int		q;
	char	qt;

	i = 0;
	q = 0;
	qt = 0;
	while (str[i])
	{
		i = new_line(str, i, &nl);
		b = q;
		q = verif_token(str[i], q, &qt);
		if (q || (b && !q))
		{
			if (qt != str[i])
				ft_putchar(str[i]);
		}
		else if (str[i] != '\\' || (str[i] == '\\' && back_line(str, i)))
			ft_putchar(str[i]);
		i++;
	}
	return (nl);
}

void			ft_echo(char *str, int *bin)
{
	int		nl;

	if (!str)
	{
		*bin = -1;
		return ;
	}
	nl = 1;
	nl = the_echo(str, nl);
	if (nl)
		ft_putchar('\n');
}
