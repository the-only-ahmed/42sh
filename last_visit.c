/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_visit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/25 19:21:53 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/19 11:33:55 by jyim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		**visit(char **env, t_env *count)
{
	ft_putendl(&env[count->old][7]);
	ft_putendl("WRONG DIRECTORY");
	return (env);
}

char			**fn_last_visit(char **env, char **pwd, t_env *count)
{
	char	*tmp;
	char	*tmp2;

	if (chdir(&env[count->old][7]) < 0)
		visit(env, count);
	if (ft_strcmp(&env[count->old][7], "/") != 0)
	{
		tmp2 = ft_strsub(&env[count->old][7], ft_strlen(&env[count->home][5]),
				ft_strlen(&env[count->old][7]));
		tmp2 = ft_strjoin("~/", tmp2);
		tmp2 = delete_chars(tmp2, '/');
	}
	else
		tmp2 = ft_strdup("/");
	if (ft_strcmp(tmp2, "~/") == 0)
		ft_putendl("~");
	else
		ft_putendl(tmp2);
	ft_strdel(&tmp2);
	tmp = ft_strdup(&env[count->old][7]);
	env[count->old] = ft_strjoin("OLDPWD=", *pwd);
	*pwd = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (env);
}
