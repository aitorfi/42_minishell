/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:54:40 by alvicina          #+#    #+#             */
/*   Updated: 2024/02/01 12:03:53 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_signal_child_builtin(int signal)
{
	if (signal == SIGINT)
		exit (2);
	else if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3", 1);
		exit (3);
	}
}

void	ft_signal_child(int signal)
{
	if (signal == SIGINT)
		ft_putstr_fd("\n", 1);
	else if (signal == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 1);
}

void	ft_signal_father(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_result = 1;
	}
}
