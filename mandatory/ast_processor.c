/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 11:20:53 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/23 19:47:44 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	read_ast_node_recursive(t_ast *node, int rfd, int wfd, t_mshell *mshell);
static int	read_ast_node_pipe(t_ast *node, int wfd, t_mshell *mshell);
static int	read_ast_node_out_redir(t_ast *node, t_mshell *mshell);
static int	read_ast_node_in_redir(t_ast *node, t_mshell *mshell);

void	process_ast(t_ast **ast, t_mshell *mshell)
{
	read_ast_node_recursive(ast[0], DEFAULT_FD, DEFAULT_FD, mshell);
}

static int	read_ast_node_recursive(t_ast *node, int rfd, int wfd, t_mshell *mshell)
{
	if (!node)
		return (EXIT_SUCCESS);
	if (node->operation == PIPE_OP)
		return (read_ast_node_pipe(node, wfd, mshell));
	else if (node->operation == COMMAND_OP)
		return (read_ast_node_command(node, rfd, wfd, mshell));
	else if (node->operation == OUT_REDIR_OP || node->operation == OUT_REDIR_APPEND_OP)
		return (read_ast_node_out_redir(node, mshell));
	else if (node->operation == IN_REDIR_OP || node->operation == IN_REDIR_APPEND_OP)
		return (read_ast_node_in_redir(node, mshell));
	read_ast_node_recursive(node->left, DEFAULT_FD, DEFAULT_FD, mshell);
	read_ast_node_recursive(node->right, DEFAULT_FD, DEFAULT_FD, mshell);
	return (EXIT_SUCCESS);
}

static int	read_ast_node_pipe(t_ast *node, int wfd, t_mshell *mshell)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
		return (notify_error("Error"));
	if (read_ast_node_recursive(node->left, DEFAULT_FD, pipe_fds[1], mshell) != EXIT_SUCCESS)
		return (close_massive(pipe_fds[0], pipe_fds[1]));
	if (read_ast_node_recursive(node->right, pipe_fds[0], wfd, mshell) != EXIT_SUCCESS)
		return (close_massive(pipe_fds[0], pipe_fds[1]));
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	return (EXIT_SUCCESS);
}

static int	read_ast_node_out_redir(t_ast *node, t_mshell *mshell)
{
	int	fd;
	int	exit_code;

	if (node->operation == OUT_REDIR_OP)
		fd = open(node->right->path, O_WRONLY | O_CREAT | O_TRUNC);
	else
		fd = open(node->right->path, O_WRONLY | O_CREAT | O_APPEND);
	if (fd == -1)
		return (notify_error("Error"));
	exit_code = read_ast_node_recursive(node->left, DEFAULT_FD, fd, mshell);
	close(fd);
	return (exit_code);
}

static int	read_ast_node_in_redir(t_ast *node, t_mshell *mshell)
{
	int	fd;
	int	exit_code;

	fd = open(node->right->path, O_RDONLY);
	if (fd == -1)
		return (notify_error("Error"));
	exit_code = read_ast_node_recursive(node->left, fd, DEFAULT_FD, mshell);
	close(fd);
	return (exit_code);
}
