/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 09:05:46 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 18:30:30 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_tree	*add_node(int bol, char *cmd)
{
	t_tree		*new;

	new = (t_tree *)malloc(sizeof(t_tree));
	new->left = NULL;
	new->right = NULL;
	new->bin = 0;
	new->father = NULL;
	new->done = 0;
	new->bol = bol;
	new->cmd = ft_strdup(cmd);
	return (new);
}

int				add_tree(t_tree **tree, int bol, char *cmd, int x)
{
	if (*tree == NULL)
		*tree = add_node(bol, cmd);
	else
	{
		if ((*tree)->left && (*tree)->left->bol != 0)
			x = add_tree(&((*tree)->left), bol, cmd, x);
		if ((*tree)->right && (*tree)->right->bol != 0)
			x = add_tree(&((*tree)->right), bol, cmd, x);
		if (!(*tree)->left && !x)
		{
			(*tree)->left = add_node(bol, cmd);
			(*tree)->left->father = (*tree);
			return (1);
		}
		else if (!(*tree)->right && !x)
		{
			(*tree)->right = add_node(bol, cmd);
			(*tree)->right->father = (*tree);
			return (1);
		}
	}
	return (x);
}

static char		**fill_tree(t_parse *s, char *line)
{
	s->tree = NULL;
	s->list = NULL;
	s->tabl = ft_strsplit_spec(line);
	s->tabl = subs(s->tabl);
	s->tabl = gestion_erreur(s->tabl);
	if (!s->tabl)
		return (NULL);
	s->tabl = adds(s->tabl);
	s->high = high_prio(s->tabl, -1);
	s->i = count_tab(s->tabl) - 1;
	s->start = s->i;
	s->end = s->i;
	return (s->tabl);
}

static void		begin_constructor(t_parse *s)
{
	while (s->i > 0)
	{
		if (priority(s->tabl[s->i]) == s->high)
		{
			if (!s->high)
			{
				s->tabl[s->i] = the_star(s->tabl[s->i]);
				s->tabl[s->i] = match_compare(s->tabl[s->i]);
			}
			add_tree(&(s->tree), s->high, s->tabl[s->i], 0);
			s->start = s->i + 1;
			s->list = add_end(s->list, splits(s->tabl, s->start, s->end));
			s->end = s->i - 1;
		}
		s->i--;
	}
	s->list = add_end(s->list, splits(s->tabl, s->i, s->end));
	s->tmp = s->list;
	while (s->list->next)
		s->list = s->list->next;
}

t_tree			*parser(char *line)
{
	t_parse		s;

	if (!(s.tabl = fill_tree(&s, line)))
		return (NULL);
	begin_constructor(&s);
	while (s.list)
	{
		s.i = -1;
		while (s.list->array[0])
		{
			s.i = high_prio_pos(s.list->array, s.i);
			s.high = priority(s.list->array[s.i]);
			if (!s.high)
			{
				s.list->array[s.i] = the_star(s.list->array[s.i]);
				s.list->array[s.i] = match_compare(s.list->array[s.i]);
			}
			add_tree(&(s.tree), s.high, s.list->array[s.i], 0);
			s.list->array = change_tab(s.list->array, s.i);
		}
		s.list = s.list->prev;
	}
	free_list(s.tmp);
	return (s.tree);
}
