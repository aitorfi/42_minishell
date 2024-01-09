/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:37:18 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/09 20:29:20 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO: Free ast
void	*free_ast(t_ast **ast)
{
	(void) ast;
	return (NULL);
}

void	*free_ast_node(t_ast *node)
{
	if (node->args)
		free(node->args);
	free(node);
	return (NULL);
}

t_ast	*new_node(t_operation op, char *path, char **args)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (node == NULL)
		return (NULL);
	node->operation = op;
	node->path = path;
	node->args = args;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast	*new_command_node(char *command)
{
	t_ast	*node;
	char	**args;

	args = ft_split(command, ' ');
	if (args == NULL)
		return (NULL);
	node = new_node(COMMAND_OP, args[0], args);
	if (node == NULL)
		return (free_split(args));
	free_split(args);
	return (node);
}
