/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:59:30 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/10 20:12:03 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_ast	*create_op_node(t_ast **ast, char **args, int index);
static t_ast	*get_left_node(char **args, int index);
static t_ast	*get_right_node_command(char **args, int index);
static t_ast	*get_right_node_heredoc(char **args, int index);

t_ast	**build_ast(char **args)
{
	t_ast	**ast;
	int		i;

	ast = malloc(sizeof(t_ast *));
	if (ast == NULL)
		return (NULL);
	i = 0;
	while (args[i])
	{
		if (is_operator(args[i]))
		{
			if (create_op_node(ast, args, i) == NULL)
				return (free_ast(ast));
		}
		i++;
	}
	return (ast);
}

static t_ast	*create_op_node(t_ast **ast, char **args, int index)
{
	t_ast	*node;

	node = new_node(which_operator(args[index]), NULL, NULL);
	if (node == NULL)
		return (NULL);
	if (ast[0])
		node->left = ast[0];
	if (!node->left)
	{
		node->left = get_left_node(args, index - 1);
		if (node->left == NULL)
			return (free_massive(node));
	}
	if (node->operation == PIPE_OP)
	{
		node->right = get_right_node_command(args, index + 1);
	}
	else if (node->operation == IN_REDIR_APPEND_OP)
	{
		node->right = get_right_node_heredoc(args, index + 1);
		node->operation = IN_REDIR_OP;
	}
	else
	{
		node->right = new_node(FILE_OP, args[index + 1], NULL);
	}
	if (node->right == NULL)
	{
		free_ast_node(node->left);
		return (free_massive(node));
	}
	ast[0] = node;
	return (node);
}

static t_ast	*get_left_node(char **args, int index)
{
	t_ast	*node;
	int		i;
	char	**node_args;
	int		node_args_len;

	i = index;
	while (i >= 0 && !is_operator(args[i]))
		i--;
	node_args_len = index - i;
	node_args = ft_calloc(node_args_len + 1, sizeof(char *));
	if (node_args == NULL)
		return (NULL);
	i = 0;
	while (i < node_args_len)
	{
		node_args[i] = args[index - node_args_len + i + 1];
		i++;
	}
	node = new_node(COMMAND_OP, node_args[0], node_args);
	if (node == NULL)
		return (free_massive(node_args));
	return (node);
}

static t_ast	*get_right_node_command(char **args, int index)
{
	t_ast	*node;
	int		i;
	char	**node_args;
	int		node_args_len;

	i = index;
	while (args[i] && !is_operator(args[i]))
		i++;
	node_args_len = i - index;
	node_args = ft_calloc(node_args_len + 1, sizeof(char *));
	if (node_args == NULL)
		return (NULL);
	i = 0;
	while (i < node_args_len)
	{
		node_args[i] = args[index + i];
		i++;
	}
	node = new_node(COMMAND_OP, node_args[0], node_args);
	if (node == NULL)
		return (free_massive(node));
	return (node);
}

static t_ast	*get_right_node_heredoc(char **args, int index)
{
	t_ast	*node = NULL;
	char	*line;
	// char	*hist_line;

	while (ft_strncmp(line, args[index], ft_strlen(line)))
	{

	}
	return (node);
}
