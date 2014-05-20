/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/01 12:18:15 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 18:20:23 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		verif_chevr(char *str)
{
	if (!ft_strcmp(str, ">"))
		return (1);
	else if (!ft_strcmp(str, ">>"))
		return (1);
	else if (!ft_strcmp(str, ">|"))
		return (1);
	else if (!ft_strcmp(str, "<"))
		return (1);
	else if (!ft_strcmp(str, "<<"))
		return (1);
	return (0);
}

static int		verif_or(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (1);
	else if (!ft_strcmp(str, "||"))
		return (1);
	else if (!ft_strcmp(str, "&"))
		return (1);
	else if (!ft_strcmp(str, "&&"))
		return (1);
	return (0);
}

static char		**gest_err(int *i, char **tab)
{
	if ((*i == 0) || (*i > 0 && priority(tab[*i - 1]) > priority(tab[*i])))
		tab = decale_deb(tab, *i, "more");
	if ((*i >= 2) && !ft_strcmp(tab[*i], "<") && priority(tab[*i - 2]))
	{
		tab = decale_deb(tab, *i, THE_CREED);
		tab = decale_deb(tab, *i + 1, "more");
		*i += 2;
	}
	return (tab);
}

char			**gestion_erreur(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		if (verif_chevr(tab[i]))
		{
			if ((tab[i + 1] && priority(tab[i + 1]) != 0) || (!tab[i + 1]))
			{
				ft_printf("parse error near '\\n'\n");
				return (NULL);
			}
			tab = gest_err(&i, tab);
		}
		else if (verif_or(tab[i]))
		{
			if ((i == 0) || (i > 0 && priority(tab[i - 1]) > priority(tab[i])))
			{
				ft_printf("parse error near '%s'\n", tab[i]);
				return (NULL);
			}
		}
		i++;
	}
	return (tab);
}
