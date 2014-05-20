/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chevron2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 09:58:37 by jyim              #+#    #+#             */
/*   Updated: 2014/03/27 18:00:55 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		chevron_left2(t_tree **tree, char **env, t_env *count, int vec)
{
	if (!ft_strcmp((*tree)->left->cmd, THE_CREED))
	{
		(*tree)->left->bol = 0;
		(*tree)->left->cmd = ft_strdup((*tree)->left->right->cmd);
	}
	if (!vec)
		(*tree) = verif_chev(*tree);
	if (left_if(tree))
		chevron(&((*tree)->father), env, count);
	else if (left_else(tree))
	{
		(*tree)->father->left->cmd = ft_strdup((*tree)->cmd);
		pipex(&((*tree)->father), env, count);
	}
	else if (ft_strcmp((*tree)->cmd, "<<") == 0)
		fn_double_chev(*tree, env, count);
	else
		fn_chev_2(*tree, env, count);
}

void			chevron_left(t_tree **tree, char **env, t_env *count, int vec)
{
	t_tree		*tmp;

	tmp = (*tree);
	(*tree)->left->done = 1;
	(*tree)->right->done = 1;
	(*tree)->done = 1;
	if (!vec && verif_chev(*tree) != *tree)
	{
		while (tmp->father && priority(tmp->father->cmd) == 2)
		{
			tmp->father->left->done = 1;
			tmp->father->right->done = 1;
			tmp = tmp->father;
		}
	}
	chevron_left2(tree, env, count, vec);
}
