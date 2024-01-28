/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorfi <aitorfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:59:30 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/28 13:34:59 by aitorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_ast	*create_node(
					t_ast **ast, char **args, int index, t_mshell *mshell);
static t_ast	*get_right_node(
					t_ast *node, char **args, int index, t_mshell *mshell);
static t_ast	**build_single_cmd_ast(
					t_ast **ast, char **args, t_mshell *mshell);

t_ast	**build_ast(char **args, t_mshell *mshell)
{
	t_ast	**ast;
	t_ast	*node;
	int		i;

	ast = ft_calloc(1, sizeof(t_ast *));
	if (ast == NULL)
		return (notify_error_ptr("Error al alojar el AST"));
	i = 0;
	while (args[i])
	{
		if (which_operator(args[i]))
		{
			node = create_node(ast, args, i, mshell);
			if (node == NULL)
				return (free_ast(ast));
			ast[0] = node;
		}
		i++;
	}
	if (!ast[0])
		ast = build_single_cmd_ast(ast, args, mshell);
	return (ast);
}

static t_ast	*create_node(
					t_ast **ast, char **args, int index, t_mshell *mshell)
{
	t_ast	*node;

	node = new_node(which_operator(args[index]), NULL, NULL, NULL);
	if (node == NULL)
		return (NULL);
	if (ast[0])
		node->left = ast[0];
	else
		node->left = get_left_node(args, index - 1, mshell);
	if (node->left == NULL)
		return (free_ast_node(node));
	node->left->parent = node;
	node->right = get_right_node(node, args, index, mshell);
	if (node->right == NULL)
	{
		free_ast_node(node->left);
		return (free_ast_node(node));
	}
	node->right->parent = node;
	return (node);
}

static t_ast	*get_right_node(
					t_ast *node, char **args, int index, t_mshell *mshell)
{
	t_ast	*right_node;
	char	*path;

	if (node->operation == PIPE_OP)
		return (get_right_node_command(args, index + 1, mshell));
	if (node->operation == IN_REDIR_APPEND_OP)
		return (get_right_node_heredoc(args, index + 1, mshell));
	path = ft_strdup(args[index + 1]);
	if (path == NULL)
		return (notify_error_ptr("Error al alojar el path del nodo del AST"));
	right_node = new_node(FILE_OP, path, NULL, NULL);
	if (right_node == NULL)
		free(path);
	return (right_node);
}

static t_ast	**build_single_cmd_ast(
					t_ast **ast, char **args, t_mshell *mshell)
{
	ast[0] = get_right_node_command(args, 0, mshell);
	if (ast[0] == NULL)
		return (free_ast(ast));
	return (ast);
}
