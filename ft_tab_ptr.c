/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/07 15:52:19 by nsavry            #+#    #+#             */
/*   Updated: 2014/03/27 17:23:07 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "shell.h"

char	**ft_init_tab(void)
{
	char	**array;

	array = malloc(sizeof(char *) * 9);
	array[0] = ft_strdup("\033[D");
	array[1] = ft_strdup("\033[C");
	array[2] = ft_strdup("\033[A");
	array[3] = ft_strdup("\033[B");
	array[4] = ft_dup_char(127);
	array[5] = ft_dup_char(0x04);
	array[6] = ft_dup_char(0x0C);
	array[7] = ft_dup_char(9);
	array[8] = NULL;
	return (array);
}

void	ft_init_fn(void)
{
	g_ft_list[0] = ft_larrow;
	g_ft_list[1] = ft_rarrow;
	g_ft_list[2] = ft_uarrow;
	g_ft_list[3] = ft_darrow;
	g_ft_list[4] = ft_delete;
	g_ft_list[5] = ft_ctrl_d;
	g_ft_list[6] = ft_ctrl_l;
	g_ft_list[7] = ft_completion;
	g_ft_list[8] = ft_other;
}

void	*ft_seek(char *buf, t_term *term)
{
	char	**array;
	int		i;
	int		len;

	(void)term;
	array = ft_init_tab();
	i = 0;
	while (array[i] != NULL)
	{
		len = ft_strlen(array[i]);
		if (ft_strncmp(array[i], buf, len) == 0)
			break ;
		i++;
	}
	return (g_ft_list[i]);
}
