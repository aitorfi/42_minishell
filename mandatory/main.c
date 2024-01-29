/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:07:12 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/29 20:12:47 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_result;

static t_mshell	*init(char **envp);
static int		readline_loop(char *prompt, t_mshell *mshell);
static int		process_line(char *line, int *read_next, t_mshell *mshell);
static int		is_terminating_cmd(t_ast **ast);

int	main(int argc, char **argv, char **envp)
{
	t_mshell	*mshell;
	int			exit_status;

	(void) argc; // Esto es para que no de error de parámetro sin usar.
	(void) argv; // Esto es para que no de error de parámetro sin usar.
	set_signal_handlers();
	mshell = init(envp);
	if (mshell == NULL)
		exit(notify_error("Error al crear los parámetros de la shell"));
	exit_status = readline_loop("minishell> ", mshell);
	if (access(mshell->heredoc_path, F_OK) == 0)
	{
		if (unlink(mshell->heredoc_path) == -1)
			perror("Error al eliminar el heredoc");
	}
	free_split(mshell->env_custom);
	free(mshell->heredoc_path);
	free(mshell);
	return (exit_status);
}

static t_mshell	*init(char **envp)
{
	t_mshell	*mshell;

	mshell = ft_calloc(1, sizeof(t_mshell));
	if (mshell == NULL)
		return (NULL);
	mshell->env_custom = do_env_init(envp, 0);
	if (mshell->env_custom == NULL)
		return (free_massive(mshell));
	mshell->heredoc_path = get_heredoc_path(mshell->env_custom);
	if (mshell->heredoc_path == NULL)
	{
		free_split(mshell->env_custom);
		return (free_massive(mshell));
	}
	mshell->stdout_fd = dup(STDOUT_FILENO);
	mshell->stdin_fd = dup(STDIN_FILENO);
	if (mshell->stdout_fd == -1 || mshell->stdin_fd == -1)
	{
		free_split(mshell->env_custom);
		return (free_massive(mshell->heredoc_path, mshell));
	}
	return (mshell);
}

static int	readline_loop(char *prompt, t_mshell *mshell)
{
	char	*line;
	int		read_next;

	read_next = 1;
	while (read_next)
	{
		line = readline(prompt);
		if (line == NULL)
		{
			rl_clear_history();
			return (notify_error("Error al leer el input del usuario"));
		}
		add_history(line);
		if (process_line(line, &read_next, mshell) != EXIT_SUCCESS)
		{
			rl_clear_history();
			return (free_massive_exit_failure(line));
		}
		free(line);
	}
	rl_clear_history();
	return (g_result);
}

static int	process_line(char *line, int *read_next, t_mshell *mshell)
{
	char	**line_split;
	t_ast	**ast;

	line_split = preprocess(line, mshell);
	if (line_split == NULL)
		return (EXIT_FAILURE);
	ast = build_ast(line_split, mshell);
	free_split(line_split);
	if (ast == NULL)
		return (EXIT_FAILURE);
	mshell->ast = ast;
	if (process_ast(ast, mshell) != EXIT_SUCCESS)
	{
		free_ast(ast);
		return (EXIT_FAILURE);
	}
	*read_next = !is_terminating_cmd(ast);
	free_ast(ast);
	return (EXIT_SUCCESS);
}

static int	is_terminating_cmd(t_ast **ast)
{
	int	path_len;

	if (!ast[0]->left && !ast[0]->right && ast[0]->operation == COMMAND_OP)
	{
		path_len = ft_strlen(ast[0]->path);
		if (!ft_strncmp(ast[0]->path, "exit", path_len)
			&& can_do_exit(ast[0]->args))
		{
			return (1);
		}
	}
	return (0);
}
