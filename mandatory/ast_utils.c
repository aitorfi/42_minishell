/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:37:18 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/14 11:10:38 by afidalgo         ###   ########.fr       */
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
		return (NULL);
	node->operation = op;
	node->path = path;
	node->args = args;
	node->limit = limit;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	print_ast(t_ast *node, int depth)
{
	int	i;

	if (node)
	{
		i = 0;
		while (i < depth)
		{
			ft_printf("|    ");
			i++;
		}
		ft_printf("operation = %s ", which_operator_str(node->operation));
		ft_printf("path = %s ", node->path);
		ft_printf("limit = %s ", node->limit);
		if (node->args)
		{
			i = 0;
			while (node->args[i])
			{
				ft_printf("arg %d = %s ", i + 1, node->args[i]);
				i++;
			}
		}
		ft_printf("\n");
		print_ast(node->left, depth + 1);
		print_ast(node->right, depth + 1);
	}
}
