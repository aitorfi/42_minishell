/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:07:12 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/23 18:52:06 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_mshell	*init(char **envp);
static int	readline_loop(char *prompt, t_mshell *mshell);

int	main(int argc, char **argv, char **envp)
{
	t_mshell	*mshell;

	(void) argc; // Esto es para que no de error de parámetro sin usar.
	(void) argv; // Esto es para que no de error de parámetro sin usar.
	set_signal_handlers();
	mshell = init(envp);
	if (mshell == NULL)
		exit(EXIT_FAILURE);
	if (readline_loop("minishell> ", mshell) == EXIT_FAILURE)
	{
		free_split(mshell->env_custom);
		free(mshell);
		exit(EXIT_FAILURE);
	}
	return (0);
}

static t_mshell	*init(char **envp)
{
	t_mshell	*mshell;

	mshell = ft_calloc(1, sizeof(t_mshell));
	if (mshell == NULL)
		exit(EXIT_FAILURE);
	mshell->env_custom = do_env_init(envp, 0);
	if (mshell->env_custom == NULL)
		return (free_massive(mshell));
	mshell->stdout_fd = dup(STDOUT_FILENO);
	return (mshell);
}

static int	readline_loop(char *prompt, t_mshell *mshell)
{
	char	*line;
	char	**line_split;
	t_ast	**ast;

	while (1)
	{
		line = readline(prompt);
		if (line == NULL)
			return (EXIT_FAILURE);
		add_history(line);
		line_split = preprocess(line, mshell);
		ast = build_ast(line_split, mshell);
		if (ast == NULL)
		{
			free_split(line_split);
			return (free_massive_exit_failure(line));
		}
		free_split(line_split);
		process_ast(ast, mshell);
		// TODO: Proteger errores en process_ast
		free_ast(ast);
		free(line);
	}
	// TODO: Esta función nunca llega a ejecutarse, hay que ponerla en la función 
	// TODO: que se encargue de liberar toda la memoria antes de terminar el programa.
	rl_clear_history();
	return (EXIT_SUCCESS);
}
