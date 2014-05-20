/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 05:03:29 by nsavry            #+#    #+#             */
/*   Updated: 2014/03/27 18:43:48 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "shell.h"
#include "libft.h"

void	ft_signal(void)
{
	signal(SIGINT, &ft_ctrl_c);
	signal(SIGHUP, &ft_def_term);
	signal(SIGTERM, &ft_def_term);
	signal(SIGSTOP, &ft_def_term);
	signal(SIGCONT, &ft_def_term);
	signal(SIGSEGV, &ft_def_term);
	signal(SIGQUIT, &ft_def_term);
	signal(SIGFPE, &ft_def_term);
	signal(SIGALRM, &ft_def_term);
	signal(SIGKILL, &ft_def_term);
	signal(SIGABRT, &ft_def_term);
	signal(SIGUSR1, &ft_def_term);
	signal(SIGUSR2, &ft_def_term);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGSTOP, SIG_IGN);
}
