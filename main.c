/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 02:17:26 by jyim              #+#    #+#             */
/*   Updated: 2014/03/27 19:14:09 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			**env_en_dur(void)
{
	char	**env;

	env = (char**)malloc(sizeof(char*) * 7);
	env[0] = ft_strdup("PATH=");
	env[1] = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	env[2] = ft_strjoin("PWD=", getcwd(NULL, 0));
	env[3] = ft_strdup("SHLVL=1");
	env[4] = ft_strdup("TERM=xterm-256color");
	env[5] = ft_strdup("_=/usr/bin/env");
	env[6] = NULL;
	return (env);
}

static void		the_loop(char **env, t_env *count)
{
	char	*line;
	t_tree	*tree;

	ft_init_fn();
	g_glob.array = ft_create_history();
	g_glob.nb = 49;
	while (1)
	{
		ft_init_term(1);
		line = ft_termcaps(get_prompt(env, count));
		line = line_to_verif(line);
		ft_def_term(1);
		if (line)
			line = variables(line, env, count);
		if (!line || (line && line[0] == '\0'))
			continue ;
		tree = parser(line);
		if (!tree)
			continue ;
		env = work_on(tree, env, count);
		ft_strdel(&line);
		free_tree(&tree);
	}
}

void			off_shell(char **env, t_env *count, char **av)
{
	char	*line;
	t_tree	*tree;

	line = ft_strdup(av[2]);
	line = line_to_verif(line);
	if (!line || (line && line[0] == '\0'))
		return ;
	tree = parser(line);
	if (!ft_strcmp(av[1], "-c"))
		work_on(tree, env, count);
	ft_strdel(&line);
	free_tab(&env);
	free_tree(&tree);
}

int				main(int ac, char **av, char **environ)
{
	char	**env;
	t_env	*count;

	if (!environ[0])
		environ = env_en_dur();
	if (ac != 1 && ac != 3)
		return (-1);
	count = (t_env *)malloc(sizeof(t_env));
	env = make_env(&count, environ);
	get_env(env);
	get_count(count);
	if (ac == 3)
		off_shell(env, count, av);
	else
		the_loop(env, count);
	return (0);
}
