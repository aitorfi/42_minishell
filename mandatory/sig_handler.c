/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:47:08 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/14 14:00:25 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	set_signal_handlers(void)
{
	//? Los procesos hijo tendrán las señales anuladas también?

	// TODO: Al recibir un ctrl-C el comando que se este ejecutando en la minishell debe terminar
	// TODO: Si no se puede enviar un SIGINT al proceso hijo se pueden usar las seles SIGUSR1 y SIGUSR2

	// TODO: La shell debe terminal al recibir una señal ctrl-D (EOF en stdin)
}
