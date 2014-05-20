/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_norme.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 02:12:38 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 09:47:09 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_NORME_H
# define LIST_NORME_H

typedef struct		s_spaces
{
	int				i;
	int				j;
	int				q;
	char			qt;
}					t_spaces;

typedef struct		s_e
{
	int				i;
	int				bol;
	char			**env_res;
	char			**tabl;
	char			**cmd;
	t_env			*count;
}					t_e;

typedef struct		s_spec
{
	int				i;
	int				j;
	int				q;
	int				p;
	int				word;
	char			qt;
	char			**tabl;
}					t_spec;

typedef struct		s_miss
{
	int				a;
	int				c;
	int				i;
	int				j;
	int				p;
	char			*str;
}					t_miss;

typedef struct		s_dlspaces
{
	char			**tmp;
	int				i;
	int				i2;
	int				q;
	char			qt;
	size_t			cnt;
}					t_dlspaces;

typedef struct		s_parse
{
	char			**tabl;
	t_l				*list;
	t_l				*tmp;
	t_tree			*tree;
	int				i;
	int				start;
	int				end;
	int				high;
}					t_parse;

typedef struct		s_others
{
	char			*cmd;
	char			**env;
	int				*bol;
	int				*bin;
}					t_others;

typedef struct		s_in_other
{
	char			*cmd;
	char			*tmp;
	char			*pwd;
	char			**array;
	int				x;
	int				bol;
}					t_in_other;

typedef struct		s_cmp
{
	int				i;
	char			**tabl;
	char			**loop;
	char			*tmp;
	char			*g;
}					t_cmp;

typedef struct		s_tmp
{
	int				i;
	int				i2;
	int				j;
	int				b;
	int				len;
	char			**tmp;
	char			*ch;
}					t_tmp;

typedef struct		s_why
{
	char			*path;
	char			**tabl;
	char			*pattern;
	char			*ch;
	DIR				*directory;
	int				x;
	int				i;
}					t_why;

typedef struct		s_complete
{
	DIR				*directory;
	char			*mot;
	char			**env;
	t_env			*count;
	char			**tableau;
	int				begin;
	int				len;
	char			*ch;
	char			*tmp;
	int				fubs;
	t_why			e;
}					t_complete;

typedef struct		s_ltverif
{
	char			**tabl;
	int				i;
	int				q;
	int				j;
	char			qt;
}					t_ltverif;

typedef struct		s_mlmp
{
	int				i;
	int				j;
	int				x;
	char			**tabl;
}					t_mlmp;

typedef struct		s_paths
{
	int				i;
	int				j;
	int				x;
	char			**tabl;
	char			**mat;
	char			*str;
}					t_paths;

typedef struct		s_delqt
{
	int				i;
	int				q;
	int				a;
	char			qt;
}					t_delqt;

#endif
