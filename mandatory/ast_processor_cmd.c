/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_processor_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:46:22 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/25 19:11:44 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	modify_stdio(int rfd, int wfd);
static void	execute_command_in_child_process(t_ast *node, t_mshell *mshell);
static void	revert_stdio(int rfd, int wfd, t_mshell *mshell);

int	read_ast_node_command(t_ast *node, int rfd, int wfd, t_mshell *mshell)
{
	modify_stdio(rfd, wfd);
	if (is_builtin(node->args[0]) && !node->parent)
		g_result = execute_builtin(node, mshell, 1);
	else
		execute_command_in_child_process(node, mshell);
	revert_stdio(rfd, wfd, mshell);
	return (EXIT_SUCCESS);
}

static void	modify_stdio(int rfd, int wfd)
{
	if (rfd >= 0)
		dup2(rfd, STDIN_FILENO);
	if (wfd >= 0)
		dup2(wfd, STDOUT_FILENO);
}

static void	execute_command_in_child_process(t_ast *node, t_mshell *mshell)
{
	int	pid;

	pid = fork();
	if (pid)
	{
		waitpid(pid, &g_result, 0);
	}
	else
	{
		if (is_builtin(node->args[0]))
			exit(execute_builtin(node, mshell, 0));
		execve(node->path, node->args, mshell->env_custom);
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

static void	revert_stdio(int rfd, int wfd, t_mshell *mshell)
{
	if (rfd >= 0)
	{
		dup2(mshell->stdin_fd, STDIN_FILENO);
		close(rfd);
	}
	if (wfd >= 0)
	{
		dup2(mshell->stdout_fd, STDOUT_FILENO);
		close(wfd);
	}
}
