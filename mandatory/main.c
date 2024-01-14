/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:07:12 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/14 10:35:50 by afidalgo         ###   ########.fr       */
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
	char	**line_split;
	t_ast	**ast;

	while (1)
	{
		line = readline(prompt);
		if (line == NULL)
			exit(EXIT_FAILURE);
		line_split = preprocess(line);
		ast = build_ast(line_split);
		if (ast == NULL)
		{
			free_split(line_split);
			free(line);
			exit(EXIT_FAILURE);
		}
		free_split(line_split);
		if (handle_history(line, ast) == EXIT_FAILURE)
		{
			free_ast(ast);
			free(line);
			exit(EXIT_FAILURE);
		}
		print_ast(ast[0], 0); // TODO: Esta linea hay que quitarla y eliminar la función
		process_ast(ast);
		free_ast(ast);
		free(line);
	}
	// TODO: Esta función nunca llega a ejecutarse, hay que ponerla en la función 
	// TODO: que se encargue de liberar toda la memoria antes de terminar el programa.
	rl_clear_history();
}
