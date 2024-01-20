/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 11:20:53 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/20 14:24:33 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	read_ast_node_recursive(t_ast *node, int rfd, int wfd, t_mshell *mshell);
static int	read_ast_node_pipe(t_ast *node, int wfd, t_mshell *mshell);
static int	read_ast_node_command(t_ast *node, int rfd, int wfd, t_mshell *mshell);

void	process_ast(t_ast **ast, t_mshell *mshell)
{
	read_ast_node_recursive(ast[0], -1, -1, mshell);
}

static int	read_ast_node_recursive(t_ast *node, int rfd, int wfd, t_mshell *mshell)
{
	if (!node)
		return (EXIT_SUCCESS);
	if (node->operation == PIPE_OP)
	{
		return (read_ast_node_pipe(node, wfd, mshell));
	}
	else if (node->operation == COMMAND_OP)
	{
		return (read_ast_node_command(node, rfd, wfd, mshell));
	}
	else
	{
		read_ast_node_recursive(node->left, -1, -1, mshell);
		read_ast_node_recursive(node->right, -1, -1, mshell);
	}
	return (EXIT_SUCCESS);
}

static int	read_ast_node_pipe(t_ast *node, int wfd, t_mshell *mshell)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
		return (notify_error("Error"));
	if (read_ast_node_recursive(node->left, -1, pipe_fds[1], mshell) == EXIT_FAILURE)
		return (close_massive(pipe_fds[0], pipe_fds[1]));
	if (read_ast_node_recursive(node->right, pipe_fds[0], wfd, mshell) == EXIT_FAILURE)
		return (close_massive(pipe_fds[0], pipe_fds[1]));
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	return (EXIT_SUCCESS);
}

static int	read_ast_node_command(t_ast *node, int rfd, int wfd, t_mshell *mshell)
{
	int	pid;

	if (rfd >= 0)
		dup2(rfd, STDIN_FILENO);
	if (wfd >= 0)
		dup2(wfd, STDOUT_FILENO);
	pid = fork();
	if (pid)
	{
		waitpid(pid, NULL, 0);
	}
	else
	{
		if (is_builtin(node->args[0]))
			exit(execute_builtin(node, mshell));
		execve(node->path, node->args, NULL);
		perror("Error");
		exit(EXIT_FAILURE);
	}
	write(mshell->stdout_fd, "comando ejecutado\n", strlen("comando ejecutado\n"));
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
	return (EXIT_SUCCESS);
}
