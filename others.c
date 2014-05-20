/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 15:03:00 by jyim              #+#    #+#             */
/*   Updated: 2014/03/27 16:53:13 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		**is_else(t_in_other *e, t_others *s, t_env *count)
{
	e->array = ft_strsplit_spaces(e->cmd, ' ', 0);
	if (ft_strcmp(e->array[0], "setenv") == 0)
		ft_setenv(e->array, s->env, s->bin);
	else if (!ft_strcmp(e->array[0], "unsetenv") ||
			!ft_strcmp(e->array[0], "unset"))
		ft_unsetenv(e->array, s->env, count, s->bin);
	else if (ft_strcmp(e->array[0], "export") == 0)
		s->env = ft_exports(s->env, e->array);
	else
	{
		free_tab(&(e->array));
		return (s->env);
	}
	free_tab(&(e->array));
	return (NULL);
}

static void		leaving(char **tab, int leave)
{
	if (leave)
	{
		if (tab[1] && ft_strisint(tab[1]))
			leave = ft_atoi(tab[1]);
		else if (tab[1])
			leave = 255;
		else
			leave = 0;
		exit(leave);
	}
}

static void		the_exit(char *cmd)
{
	char	**env;
	char	**tab;
	int		leave;

	leave = 1;
	tab = ft_strsplit(cmd, ' ');
	ft_printf("%sexit %s:'(%s\n", c(PINK), c(GRBL), c(NO));
	if (tab[1] && !ft_strisint(tab[1]))
		ft_printf("42sh: exit: %s: numeric argument required\n", tab[1]);
	if (count_tab(tab) > 2)
	{
		ft_putendl("42sh: exit: too many arguments\n");
		if (ft_strisint(tab[1]))
			leave = 0;
	}
	env = get_env(NULL);
	free_tab(&env);
	leaving(tab, leave);
}

static char		**the_beginning(t_in_other *e, t_others *s, t_env *count)
{
	char	**tab;

	e->bol = 0;
	if (other_cd(e))
	{
		if ((tab = begin_oth(e, s, count)))
			return (tab);
		e->bol = 1;
	}
	else if (ft_strcmp("cd -", e->cmd) == 0)
	{
		if ((tab = cd_less(e, s, count)))
			return (tab);
		e->bol = 1;
	}
	else if (ft_strncmp("cd ", e->cmd, 3) == 0)
	{
		if ((tab = cd_space(e, s, count)))
			return (tab);
		e->bol = 1;
	}
	return (NULL);
}

char			**others(t_others *s, t_env *count)
{
	t_in_other		e;
	char			**tab;

	fill_oth(&e, s, count);
	if ((tab = the_beginning(&e, s, count)))
		return (tab);
	else if (e.bol == 0)
	{
		if (ft_strncmp("echo ", e.cmd, 5) == 0)
			ft_echo(&(e.cmd[5]), s->bin);
		else if (ft_strncmp("fuck ", e.cmd, 5) == 0)
			ft_fuck(e.cmd, s->bin);
		else if (ft_strncmp(e.cmd, "exit", 4) == 0)
			the_exit(e.cmd);
		else if (ft_strncmp(e.cmd, "env", 3) == 0)
			ft_the_env(e.cmd, s->env, count, s->bin);
		else if ((tab = is_else(&e, s, count)))
			return (tab);
	}
	*(s->bol) = 1;
	if (count->pwd != -1 && e.pwd)
		s->env[count->pwd] = ft_strjoin("PWD=", e.pwd);
	return (s->env);
}
