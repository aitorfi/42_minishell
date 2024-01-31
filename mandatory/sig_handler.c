/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:47:08 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/31 19:09:21 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

	//? Los procesos hijo tendrán las señales anuladas también?

	// TODO: Al recibir un ctrl-C el comando que se este ejecutando en la minishell debe terminar
	// TODO: Si no se puede enviar un SIGINT al proceso hijo se pueden usar las seles SIGUSR1 y SIGUSR2

	// TODO: La shell debe terminal al recibir una señal ctrl-D (EOF en stdin)

void	ft_signal_child(int signal)
{
	if (signal == SIGINT)
	{
		//ft_putstr_fd("\n", 1);
		//printf("hola\n");
		exit (0);
	}
	else if (signal == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 1);
}

void ft_signal_father(int signal)
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

void	set_signal_handlers_fork(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = ft_signal_child;
	sigaction(SIGINT, &sa,  NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_signal_handlers(void)
{
	struct sigaction	sa;
	
	rl_catch_signals = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = ft_signal_father;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
