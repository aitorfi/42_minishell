/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 11:20:53 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/27 13:18:39 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	read_ast_node(t_ast *node, int rfd, int wfd, t_mshell *mshell);
static int	read_ast_node_pipe(t_ast *node, int wfd, t_mshell *mshell);
static int	read_ast_node_out_redir(t_ast *node, int rfd, t_mshell *mshell);
static int	read_ast_node_in_redir(t_ast *node, int wfd, t_mshell *mshell);

int	process_ast(t_ast **ast, t_mshell *mshell)
{
	return (read_ast_node(ast[0], DEFAULT_FD, DEFAULT_FD, mshell));
}

static int	read_ast_node(t_ast *node, int rfd, int wfd, t_mshell *mshell)
{
	if (!node)
		return (EXIT_SUCCESS);
	if (node->operation == PIPE_OP)
		return (read_ast_node_pipe(node, wfd, mshell));
	if (node->operation == COMMAND_OP)
		return (read_ast_node_command(node, rfd, wfd, mshell));
	if (node->operation == OUT_REDIR_OP
		|| node->operation == OUT_REDIR_APPEND_OP)
		return (read_ast_node_out_redir(node, rfd, mshell));
	if (node->operation == IN_REDIR_OP
		|| node->operation == IN_REDIR_APPEND_OP)
		return (read_ast_node_in_redir(node, wfd, mshell));
	read_ast_node(node->left, DEFAULT_FD, DEFAULT_FD, mshell);
	read_ast_node(node->right, DEFAULT_FD, DEFAULT_FD, mshell);
	return (EXIT_SUCCESS);
}

static int	read_ast_node_pipe(t_ast *node, int wfd, t_mshell *mshell)
{
	int	pipe_fds[2];
	int	exit_status;

	if (pipe(pipe_fds) == -1)
		return (notify_error("Error al crear la pipe"));
	exit_status = read_ast_node(node->left, DEFAULT_FD, pipe_fds[1], mshell);
	if (exit_status != EXIT_SUCCESS)
		return (close_massive(pipe_fds[0], pipe_fds[1]));
	exit_status = read_ast_node(node->right, pipe_fds[0], wfd, mshell);
	if (exit_status != EXIT_SUCCESS)
		return (close_massive(pipe_fds[0], pipe_fds[1]));
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	return (EXIT_SUCCESS);
}

static int	read_ast_node_out_redir(t_ast *node, int rfd, t_mshell *mshell)
{
	int	fd;
	int	exit_code;

	if (node->operation == OUT_REDIR_OP)
		fd = open(node->right->path, O_RDWR | O_CREAT | O_TRUNC, 00644);
	else
		fd = open(node->right->path, O_RDWR | O_CREAT | O_APPEND, 00644);
	if (fd == -1)
		return (notify_error("Error al abrir archivo destino"));
	exit_code = read_ast_node(node->left, rfd, fd, mshell);
	close(fd);
	return (exit_code);
}

static int	read_ast_node_in_redir(t_ast *node, int wfd, t_mshell *mshell)
{
	int	fd;
	int	exit_code;

	fd = open(node->right->path, O_RDONLY);
	if (fd == -1)
		return (notify_error("Error al abrir archivo origen"));
	exit_code = read_ast_node(node->left, fd, wfd, mshell);
	close(fd);
	return (exit_code);
}
