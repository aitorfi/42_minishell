/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:07:12 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/20 14:22:52 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_mshell	*init(char **envp);
static int		readline_loop(char *prompt, t_mshell *mshell);
static int		is_terminating_cmd(t_ast **ast);

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
	free_split(mshell->env_custom);
	free(mshell);
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
	mshell->stdin_fd = dup(STDIN_FILENO);
	return (mshell);
}

static int	readline_loop(char *prompt, t_mshell *mshell)
{
	char	*line;
	char	**line_split;
	t_ast	**ast;
	int		read_next_line;

	read_next_line = 1;
	while (read_next_line)
	{
		line = readline(prompt);
		if (line == NULL)
			return (EXIT_FAILURE);
		add_history(line);
		line_split = preprocess(line);
		free(line);
		ast = build_ast(line_split, mshell);
		free_split(line_split);
		if (ast == NULL)
			return (EXIT_FAILURE);
		read_next_line = !is_terminating_cmd(ast);
		process_ast(ast, mshell);
		// TODO: Proteger errores en process_ast
		free_ast(ast);
	}
	printf("read_next_line = %d\n", read_next_line);
	rl_clear_history();
	return (g_result);
}

static int	is_terminating_cmd(t_ast **ast)
{
	return (!ast[0]->left && !ast[0]->right
		&& !ft_strncmp(ast[0]->path, "exit", ft_strlen(ast[0]->path)));
}
