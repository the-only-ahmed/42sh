/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 23:04:31 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 11:32:04 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**get_env(char **env)
{
	static char		**tenv;

	if (!tenv)
		tenv = env;
	return (tenv);
}

t_env	*get_count(t_env *count)
{
	static t_env	*cnt;

	if (!cnt)
		cnt = count;
	return (cnt);
}

int		get_prompt(char **env, t_env *count)
{
	char	*str;
	int		i;
	int		len;

	i = search_exp("USER", env);
	if (i < 0)
		str = "user";
	else
		str = &env[i][5];
	len = ft_printf("%s(%s)%s", c(RED), str, c(GREEN));
	if (ft_strrchr(env[count->pwd], '/'))
		str = ft_strrchr(env[count->pwd], '/') + 1;
	else
		str = ft_strdup("NULL");
	len += ft_printf(" %s> %s", str, c(NO));
	return (len);
}
