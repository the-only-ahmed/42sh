/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 14:47:19 by nsavry            #+#    #+#             */
/*   Updated: 2014/03/27 12:03:09 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**ft_create_history(void)
{
	char	**array;
	int		i;

	i = 0;
	array = malloc(sizeof(char *) * 51);
	while (i <= 50)
	{
		array[i] = NULL;
		i++;
	}
	return (array);
}

void	ft_add_history(char *str)
{
	int		i;

	i = 0;
	while (i != 49)
	{
		if (g_glob.array[i + 1] != NULL)
			g_glob.array[i] = ft_strdup(g_glob.array[i + 1]);
		i++;
	}
	g_glob.array[49] = ft_strdup(str);
}

void	ft_history_up(void)
{
	g_glob.nb--;
	g_glob.i = ft_strlen(g_glob.array[g_glob.nb]);
	g_glob.str = ft_strdup(g_glob.array[g_glob.nb]);
	ft_putstr(g_glob.str);
}

void	ft_history_down(void)
{
	g_glob.nb++;
	if (g_glob.nb == 50)
	{
		g_glob.i = 0;
		g_glob.str[0] = 0;
		return ;
	}
	g_glob.i = ft_strlen(g_glob.array[g_glob.nb]);
	g_glob.str = ft_strdup(g_glob.array[g_glob.nb]);
	ft_putstr(g_glob.str);
}
