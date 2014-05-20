/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 01:11:55 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/26 00:36:55 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_tree(t_tree **tree)
{
	if ((*tree)->left)
		free_tree(&((*tree)->left));
	if ((*tree)->right)
		free_tree(&((*tree)->right));
	if ((*tree)->cmd)
		ft_strdel(&((*tree)->cmd));
	if (*tree)
		free(*tree);
	*tree = NULL;
}

void	free_tab(char ***tab)
{
	int		i;

	i = 0;
	if (!(*tab))
		return ;
	while ((*tab)[i])
	{
		ft_strdel(&((*tab)[i]));
		i++;
	}
	free(*tab);
	*tab = NULL;
}

void	free_list(t_l *list)
{
	t_l		*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free_tab(&(tmp->array));
		free(tmp);
		tmp = NULL;
	}
}
