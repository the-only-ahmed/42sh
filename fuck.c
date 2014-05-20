/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuck.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 05:40:18 by ael-kadh          #+#    #+#             */
/*   Updated: 2014/03/27 11:33:46 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <signal.h>

static int		verif_d(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

static void		ft_kill_dance(int pid)
{
	ft_printf("                      /'-/) \n");
	ft_printf("                    ,/-../ \n");
	ft_printf("                   /..../ \n");
	ft_printf("             /'-/'...'/'-`., \n");
	ft_printf("          /'/.../..../......./\"-\\");
	ft_printf("%s            PID = %s%d", c(YELLOW), c(GREEN), pid, c(NO));
	ft_printf("%s FUCKED :D\n%s", c(PINK), c(NO));
	ft_printf("        ('(...'...'.... -~/'...')\n");
	ft_printf("         \\.................'...../ \n");
	ft_printf("          ''...\\.......... _..' \n");
	ft_printf("            \\..............( \n");
	ft_printf("              \\.............\\\n");
}

static void		the_kill(int pid, int *bin, char **tab, int i)
{
	if (kill(pid, 9) == -1)
	{
		*bin = -1;
		ft_printf("%s : No such process\n", tab[i]);
	}
	if (tab[i + 1])
		ft_putchar('\n');
}

void			ft_fuck(char *str, int *bin)
{
	char	**tab;
	int		i;
	int		pid;

	tab = ft_strsplit(str, ' ');
	i = 1;
	while (tab[i])
	{
		if (verif_d(tab[i]))
		{
			pid = ft_atoi(tab[i]);
			ft_kill_dance(pid);
			the_kill(pid, bin, tab, i);
		}
		else
		{
			*bin = -1;
			ft_printf("%s : No such process\n", tab[i]);
		}
		i++;
	}
}
