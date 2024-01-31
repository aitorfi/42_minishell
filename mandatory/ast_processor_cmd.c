/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_processor_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:46:22 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/31 11:10:16 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	modify_stdio(int rfd, int wfd);
static int	execute_command_in_child_process(t_ast *node, t_mshell *mshell);
static void	execute_command(t_ast *node, t_mshell *mshell);
static int	revert_stdio(int rfd, int wfd, t_mshell *mshell);

int	read_ast_node_command(t_ast *node, int rfd, int wfd, t_mshell *mshell)
{
	if (modify_stdio(rfd, wfd) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (is_builtin(node->args[0]) && !node->parent)
	{
		g_result = execute_builtin(node, mshell, 1);
	}
	else
	{
		if (execute_command_in_child_process(node, mshell) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	if (revert_stdio(rfd, wfd, mshell) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	modify_stdio(int rfd, int wfd)
{
	if (rfd >= 0 && dup2(rfd, STDIN_FILENO) == -1)
		return (notify_error("Error al modificar stdin"));
	if (wfd >= 0 && dup2(wfd, STDOUT_FILENO) == -1)
		return (notify_error("Error al modificar stdout"));
	return (EXIT_SUCCESS);
}

static int	execute_command_in_child_process(t_ast *node, t_mshell *mshell)
{
	int	pid;
	
	set_signal_handlers_fork();
	pid = fork();
	if (pid == -1)
		return (notify_error("Error al crear proceso hijo"));
	else if (pid > 0)
		waitpid(pid, &g_result, 0);
	else if (pid == 0)
		execute_command(node, mshell);
	set_signal_handlers();
	return (EXIT_SUCCESS);
}

static void	execute_command(t_ast *node, t_mshell *mshell)
{
	int	status;
	
	if (is_builtin(node->args[0]))
	{
		status = execute_builtin(node, mshell, 0);
		free_split(mshell->env_custom);
		free_ast(mshell->ast);
		free(mshell);
		rl_clear_history();
		exit(status);
	}
	execve(node->path, node->args, mshell->env_custom);
	perror("Error al ejecutar comando con execve");
	exit(EXIT_FAILURE);
}

static int	revert_stdio(int rfd, int wfd, t_mshell *mshell)
{
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	if (rfd >= 0)
	{
		close(rfd);
		if (dup2(mshell->stdin_fd, STDIN_FILENO) == -1)
			exit_status = notify_error("Error al restaurar stdin");
	}
	if (wfd >= 0)
	{
		close(wfd);
		if (dup2(mshell->stdout_fd, STDOUT_FILENO) == -1)
			exit_status = notify_error("Error al restaurar stdout");
	}
	return (exit_status);
}
