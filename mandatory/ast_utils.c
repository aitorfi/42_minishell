/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:37:18 by afidalgo          #+#    #+#             */
/*   Updated: 2024/02/04 10:42:12 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	*free_ast_recursive(t_ast *node);

void	*free_ast(t_ast **ast)
{
	free_ast_recursive(ast[0]);
	free(ast);
	return (NULL);
}

int	free_ast_status(t_ast **ast, int status)
{
	free_ast_recursive(ast[0]);
	free(ast);
	return (status);
}

static void	*free_ast_recursive(t_ast *node)
{
	if (node)
	{
		free_ast_recursive(node->left);
		free_ast_recursive(node->right);
		free_ast_node(node);
	}
	return (NULL);
}

void	*free_ast_node(t_ast *node)
{
	if (node->args)
		free_split(node->args);
	if (node->path)
		free(node->path);
	if (node->limit)
		free(node->limit);
	free(node);
	return (NULL);
}

t_ast	*new_node(t_operation op, char *path, char **args, char *limit)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (node == NULL)
		return (notify_error_ptr("Error al alojar nodo del AST"));
	node->operation = op;
	node->path = path;
	node->args = args;
	node->limit = limit;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	return (node);
}
