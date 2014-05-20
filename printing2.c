/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 03:28:26 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/25 21:26:54 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		export_typeset_aff(char **export, char **things, int i)
{
	int		x;

	while (things[++i])
	{
		x = 0;
		if (!ft_strncmp(things[i], "_", 1))
			ft_printf("typeset -r _='%s'\n", things[i]);
		else if ((x = search_exp(things[i], export)) != -1)
		{
			if (ft_strchr(export[x], '='))
				ft_printf("typeset -x %s\n", export[x]);
			else
				ft_printf("typeset -x %s=''\n", export[x]);
		}
		else if (x == 0)
			ft_printf("export : no such variable : %s\n", things[i]);
	}
}

void			aff_tab_export(char **export, char **things)
{
	int		i;

	i = -1;
	while (!things && export[++i])
	{
		if (ft_strncmp(export[i], "_=", 2) && ft_strcmp(export[i], THE_CREED))
		{
			if (ft_strchr(export[i], '='))
				ft_printf("typeset -x %s\n", export[i]);
			else
				ft_printf("typeset -x %s=''\n", export[i]);
		}
		else if (!ft_strcmp(export[i], THE_CREED))
			ft_printf("typeset -rx _=p\n");
	}
	if (things)
		export_typeset_aff(export, things, i);
}
