/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_term_resize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/22 18:12:31 by nsavry            #+#    #+#             */
/*   Updated: 2014/03/27 14:00:26 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include "shell.h"

void	ft_term_resize(int c)
{
	struct winsize	w;

	(void)c;
	ioctl(0, TIOCGWINSZ, &w);
	g_glob.l_max = w.ws_row;
	g_glob.c_max = w.ws_col;
}
