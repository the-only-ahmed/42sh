/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 05:15:23 by nsavry            #+#    #+#             */
/*   Updated: 2014/03/27 19:14:26 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_ctrl_d(t_term *term)
{
	(void)term;
	ft_putchar('\n');
	ft_def_term(0);
	exit(0);
}

void	ft_ctrl_c(int c)
{
	t_env	*count;
	char	**env;

	(void)c;
	env = get_env(NULL);
	count = get_count(NULL);
	g_glob.str[0] = 0;
	g_glob.i = 0;
	ft_putchar('\n');
	get_prompt(env, count);
}

void	ft_ctrl_l(t_term *term)
{
	char	**cmd;
	t_env	*count;
	int		bin;
	char	**env;

	(void)term;
	env = get_env(NULL);
	count = get_count(NULL);
	bin = 0;
	cmd = fn_commande("clear", env, count);
	ft_execve(cmd, env, &bin, "clear");
	get_prompt(env, count);
	ft_putstr(g_glob.str);
}
