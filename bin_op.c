/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/05 15:33:34 by jyim              #+#    #+#             */
/*   Updated: 2014/03/05 16:32:54 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		binaire_exec(t_tree **tree)
{
	if (ft_strcmp((*tree)->cmd, "||") == 0)
	{
		if ((*tree)->bin == 0)
		{
			if ((*tree)->right)
				(*tree)->right->done = 1;
			if ((*tree)->father)
				(*tree)->father->bin = -1;
		}
	}
	else
	{
		if ((*tree)->bin == -1)
		{
			if ((*tree)->right)
				(*tree)->right->done = 1;
			if ((*tree)->father)
				(*tree)->father->bin = -1;
		}
	}
}
