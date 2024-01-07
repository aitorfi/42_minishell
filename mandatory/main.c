/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:07:12 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/07 11:27:46 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	readline_loop(char *prompt);

int	main(int argc, char **argv, char **envp)
{
	(void) argc; // Esto es para que no de error de parámetro sin usar.
	(void) argv; // Esto es para que no de error de parámetro sin usar.
	(void) envp; // Esto es para que no de error de parámetro sin usar.
	set_signal_handlers();
	readline_loop("minishell> ");
	return (0);
}

static void	readline_loop(char *prompt)
{
	char	*line;
	t_ast	**ast;

	while (1)
	{
		line = readline(prompt);
		add_history(line);
		preprocess(line);
		ast = build_ast(line);
		process_ast(ast);
		// TODO: Hay que liberar el ast
		free(line);
	}
}
