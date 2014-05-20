/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/05 10:50:49 by jyim              #+#    #+#             */
/*   Updated: 2014/03/27 11:38:45 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		**make_env2(char **env)
{
	int		i;
	int		length;
	char	**tenv;

	i = 0;
	length = 0;
	while (env[length])
		length++;
	tenv = (char**)malloc(sizeof(char*) * (length));
	while (env[i])
	{
		tenv[i] = ft_strdup(env[i]);
		i++;
	}
	tenv[i] = NULL;
	return (tenv);
}

char			**ft_set_modif(char **env, char *str)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (count_tab(env) + 2));
	if (!env)
	{
		tmp[0] = ft_strdup(str);
		tmp[1] = NULL;
		return (tmp);
	}
	while (env[i])
	{
		tmp[i] = ft_strdup(env[i]);
		i++;
	}
	tmp[i] = ft_strdup(str);
	tmp[i + 1] = NULL;
	return (tmp);
}

static int		fill_the_env(t_e *envir, char *str)
{
	envir->count = (t_env *)malloc(sizeof(t_env));
	envir->i = 0;
	envir->bol = 0;
	if (ft_strcmp("env", str) == 0)
		return (1);
	return (0);
}

static void		ft_the_env2(t_env *ct, t_e *e, int *bin, char **env)
{
	t_others		s;

	s.bol = (int*)malloc(sizeof(int));
	*(s.bol) = 0;
	s.cmd = e->tabl[e->i];
	s.bin = bin;
	if (ct->path != -1)
		e->env_res = ft_set_modif(e->env_res, env[ct->path]);
	s.env = ft_strdup_tab(e->env_res, count_tab(e->env_res));
	e->count = reset_count(e->env_res, e->count);
	e->env_res = others(&s, e->count);
	if (!e->bol)
	{
		e->cmd = fn_commande(e->tabl[e->i], e->env_res, e->count);
		ft_execve(e->cmd, e->env_res, bin, e->tabl[e->i]);
	}
}

void			ft_the_env(char *str, char **env, t_env *ct, int *bin)
{
	t_e		e;

	if (fill_the_env(&e, str))
		aff_env(env);
	else
	{
		e.tabl = ft_strsplit(str, ' ');
		e.i = 1;
		if (e.tabl[1] && ft_strcmp(e.tabl[1], "-i") == 0)
		{
			e.env_res = NULL;
			e.i = 2;
		}
		else
			e.env_res = make_env2(env);
		while (e.tabl[e.i] && ft_strchr(e.tabl[e.i], '='))
		{
			e.env_res = ft_set_modif(e.env_res, e.tabl[e.i]);
			e.i++;
		}
		if (!e.tabl[e.i])
			aff_env(e.env_res);
		else
			ft_the_env2(ct, &e, bin, env);
	}
}
