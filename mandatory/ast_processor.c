/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_processor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 11:20:53 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/15 19:45:26 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	read_ast_node_recursive(t_ast *node, t_ast_node_type type, int *rfd, int *wfd);

void	process_ast(t_ast **ast)
{
	read_ast_node_recursive(ast[0], ROOT, NULL, NULL);
}

static int	read_ast_node_recursive(t_ast *node, t_ast_node_type type, int *rfd, int *wfd)
{
	int	pipe_fds[2];

	if (!node)
		return (EXIT_SUCCESS);
	if (node->operation == PIPE_OP)
	{
		if (pipe(pipe_fds) == -1)
			return (notify_error("Error"));
		read_ast_node_recursive(node->left, LEFT, NULL, pipe_fds[1]);
		read_ast_node_recursive(node->right, RIGHT, pipe_fds[0], wfd);
	}
	else
	{
		read_ast_node_recursive(node->left, LEFT, NULL, NULL);
		read_ast_node_recursive(node->right, RIGHT, NULL, NULL);
	}
	return (EXIT_SUCCESS);
}
