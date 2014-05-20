/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 02:20:42 by jyim              #+#    #+#             */
/*   Updated: 2014/03/27 19:14:19 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H

typedef struct		s_tree
{
	char			*cmd;
	int				bol;
	int				done;
	int				bin;
	struct s_tree	*father;
	struct s_tree	*right;
	struct s_tree	*left;
}					t_tree;

typedef struct		s_l
{
	char			**array;
	struct s_l		*next;
	struct s_l		*prev;
}					t_l;

typedef struct		s_env
{
	int				path;
	int				pwd;
	int				old;
	int				home;
	int				boll;
}					t_env;

typedef struct		s_glob
{
	char			*str;
	int				i;
	int				j;
	char			**array;
	int				nb;
	int				l_max;
	int				c_max;
	int				var;
}					t_glob;

typedef struct		s_term
{
	int				prompt;
	char			*tmp;
	char			*buf;
}					t_term;

#endif
