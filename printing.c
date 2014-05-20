/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/01 13:10:07 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/26 11:02:41 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	aff_list(t_l *list)
{
	if (list == NULL)
		return ;
	else
	{
		aff_tab(list->array);
		aff_list(list->next);
	}
}

void	aff_tab(char **tab)
{
	int		i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		ft_printf("%s'\n", tab[i]);
		i++;
	}
}

int		count_tab(char **tab)
{
	int		i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

void	aff_tab_e(char **tab)
{
	int		i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		if (!ft_strchr(tab[i], '='))
			ft_printf("%s=''\n", tab[i]);
		else if (ft_strncmp(tab[i], "_=", 2))
			ft_putendl(tab[i]);
		else if (!ft_strcmp(tab[i], THE_CREED))
			ft_putendl("_=export");
		i++;
	}
}

void	aff_env(char **tab)
{
	int		i;
	int		x;
	char	*l;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], THE_CREED) && (l = ft_strchr(tab[i], '=')))
		{
			x = l - tab[i];
			if (tab[i][x + 1])
				ft_printf("%s\n", tab[i]);
		}
		i++;
	}
}
