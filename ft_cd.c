/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 19:23:36 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/25 21:20:26 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			*ft_chg_home(char *str, int *bin)
{
	str = &str[5];
	if (chdir(str) == -1)
		*bin = -1;
	return (str);
}

char			*ft_direct_chdir(char *str, char *pwd, int *bin)
{
	if (chdir(str) < 0)
	{
		*bin = -1;
		ft_printf("cd: no such file or directory: %s\n", str);
		return (pwd);
	}
	str = ft_clear_pwd(str);
	return (str);
}

char			*ft_cd(char *pwd, char *line, int *bin)
{
	char	**tmp;
	char	*pwd2;

	if (ft_occ_nb(line, ' ') + ft_occ_nb(line, '\t') > 1)
		return (ft_putendl("cd: too many arguments"), pwd);
	tmp = ft_strsplit_spaces(line, ' ', 0);
	if (ft_strcmp(tmp[1], "\0") == 0 || ft_strcmp(tmp[1], ".") == 0)
		return (pwd);
	else if (tmp[1][0] == '/')
		return (ft_direct_chdir(tmp[1], pwd, bin));
	pwd = ft_strjoin(pwd, "/");
	pwd2 = ft_strjoin(pwd, tmp[1]);
	pwd = ft_clear_pwd(pwd);
	pwd2 = ft_clear_pwd(pwd2);
	if (chdir(pwd2) < 0)
	{
		*bin = -1;
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(ft_strrchr(pwd2, '/') + 1);
		return (pwd);
	}
	return (pwd2);
}
