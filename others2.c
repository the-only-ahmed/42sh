/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyim <jyim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 17:40:07 by jyim              #+#    #+#             */
/*   Updated: 2014/03/19 17:55:57 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		fill_oth(t_in_other *e, t_others *s, t_env *count)
{
	e->x = 0;
	e->array = NULL;
	if (count->pwd != -1)
		e->pwd = ft_strdup(&(s->env[count->pwd][4]));
	e->cmd = ft_strdup(s->cmd);
	e->cmd = delete_bs(e->cmd, '\\');
	e->cmd = fn_appel(e->cmd, s->env, count, &(e->x));
}

char		**begin_oth(t_in_other *e, t_others *s, t_env *count)
{
	if (count->home == -1)
	{
		ft_putendl("cd: line 4: cd: HOME not set");
		*(s->bol) = 1;
		*(s->bin) = -1;
		return (s->env);
	}
	e->tmp = ft_strdup(e->pwd);
	e->pwd = ft_chg_home(s->env[count->home], s->bin);
	if (ft_strcmp(e->pwd, e->tmp))
		s->env[count->old] = ft_strjoin("OLDPWD=", e->tmp);
	ft_strdel(&(e->tmp));
	return (NULL);
}

char		**cd_less(t_in_other *e, t_others *s, t_env *count)
{
	if (count->old == -1)
	{
		*(s->bol) = 1;
		*(s->bin) = -1;
		ft_putendl("cd: line 4: cd: OLDPWD not set");
		return (s->env);
	}
	e->tmp = ft_strjoin("OLDPWD=", &(s->env[count->pwd][4]));
	s->env = fn_last_visit(s->env, &(e->pwd), count);
	s->env[count->old] = ft_strdup(e->tmp);
	ft_strdel(&(e->tmp));
	return (NULL);
}

char		**cd_space(t_in_other *e, t_others *s, t_env *count)
{
	if (count->old == -1)
	{
		*(s->bol) = 1;
		*(s->bin) = -1;
		return (s->env);
	}
	e->tmp = ft_strdup(e->pwd);
	e->pwd = ft_strdup(ft_cd(e->pwd, e->cmd, s->bin));
	if (ft_strcmp(e->pwd, e->tmp))
		s->env[count->old] = ft_strjoin("OLDPWD=", e->tmp);
	if (e->x)
		e->pwd = getcwd(NULL, 0);
	ft_strdel(&(e->tmp));
	return (NULL);
}
