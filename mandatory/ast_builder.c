/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:59:30 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/19 17:11:41 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_ast	*create_op_node(t_ast **ast, char **args, int index, t_mshell *mshell);
static t_ast	*get_left_node(char **args, int index, t_mshell *mshell);
static t_ast	*get_right_node_command(char **args, int index, t_mshell *mshell);
static t_ast	*get_right_node_heredoc(char **args, int index);

t_ast	**build_ast(char **args, t_mshell *mshell)
{
	t_ast	**ast;
	t_ast	*node;
	int		i;

	ast = ft_calloc(1, sizeof(t_ast *));
	if (ast == NULL)
		return (NULL);
	i = 0;
	while (args[i])
	{
		if (which_operator(args[i]))
		{
			node = create_op_node(ast, args, i, mshell);
			if (node == NULL)
				return (free_ast(ast));
			ast[0] = node;
		}
		i++;
	}
	if (!ast[0])
	{
		ast[0] = get_right_node_command(args, 0, mshell);
		if (ast[0] == NULL)
			return (free_ast(ast));
	}
	return (ast);
}

static t_ast	*create_op_node(t_ast **ast, char **args, int index, t_mshell *mshell)
{
	t_ast	*node;

	node = new_node(which_operator(args[index]), NULL, NULL, NULL);
	if (node == NULL)
		return (NULL);
	if (ast[0])
		node->left = ast[0];
	if (!node->left)
	{
		node->left = get_left_node(args, index - 1, mshell);
		if (node->left == NULL)
			return (free_massive(node));
	}
	if (node->operation == PIPE_OP)
		node->right = get_right_node_command(args, index + 1, mshell);
	else if (node->operation == IN_REDIR_APPEND_OP)
		node->right = get_right_node_heredoc(args, index + 1);
	else
		node->right = new_node(FILE_OP, ft_strdup(args[index + 1]), NULL, NULL);
	if (node->right == NULL)
	{
		free_ast_node(node->left);
		return (free_massive(node));
	}
	return (node);
}

static t_ast	*get_left_node(char **args, int index, t_mshell *mshell)
{
	t_ast	*node;
	int		i;
	char	**node_args;
	int		node_args_len;
	char	*cmd_path;

	i = index;
	while (i >= 0 && !which_operator(args[i]))
		i--;
	node_args_len = index - i;
	node_args = ft_calloc(node_args_len + 1, sizeof(char *));
	if (node_args == NULL)
		return (NULL);
	i = 0;
	while (i < node_args_len)
	{
		node_args[i] = ft_strdup(args[index - node_args_len + i + 1]);
		i++;
	}
	cmd_path = append_path_to_cmd(mshell->env_custom, node_args[0]);
	if (cmd_path == NULL)
		return (free_split(node_args));
	node = new_node(COMMAND_OP, cmd_path, node_args, NULL);
	if (node == NULL)
	{
		free_split(node_args);
		return (free_massive(cmd_path));
	}
	return (node);
}

static t_ast	*get_right_node_command(char **args, int index, t_mshell *mshell)
{
	t_ast	*node;
	int		i;
	char	**node_args;
	int		node_args_len;
	char	*cmd_path;

	i = index;
	while (args[i] && !which_operator(args[i]))
		i++;
	node_args_len = i - index;
	node_args = ft_calloc(node_args_len + 1, sizeof(char *));
	if (node_args == NULL)
		return (NULL);
	i = 0;
	while (i < node_args_len)
	{
		node_args[i] = ft_strdup(args[index + i]);
		i++;
	}
	cmd_path = append_path_to_cmd(mshell->env_custom, node_args[0]);
	if (cmd_path == NULL)
		return (free_split(node_args));
	node = new_node(COMMAND_OP, cmd_path, node_args, NULL);
	if (node == NULL)
	{
		free_massive(node);
		return (free_massive(cmd_path));
	}
	return (node);
}

static t_ast	*get_right_node_heredoc(char **args, int index)
{
	t_ast	*node;
	char	*path;

	path = create_heredoc(args[index]);
	if (path == NULL)
		return (NULL);
	node = new_node(FILE_OP, path, NULL, ft_strdup(args[index]));
	if (node == NULL)
		return (free_massive(path));
	return (node);
}
