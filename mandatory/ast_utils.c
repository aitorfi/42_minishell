/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:37:18 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/07 14:13:22 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO: Free ast
void	*free_ast(t_ast **ast)
{
	(void) ast;
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
