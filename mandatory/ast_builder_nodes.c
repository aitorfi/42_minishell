/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder_nodes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:31:39 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/25 19:50:58 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**get_left_node_args(char **args, int index);
static char	**get_right_node_args(char **args, int index);

t_ast	*get_left_node(char **args, int index, t_mshell *mshell)
{
	t_ast	*node;
	char	**node_args;
	char	*cmd_path;

	node_args = get_left_node_args(args, index);
	if (node_args == NULL)
		return (NULL);
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

static char	**get_left_node_args(char **args, int index)
{
	int		i;
	char	**node_args;
	int		node_args_len;

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
		if (node_args[i] == NULL)
			return (free_split(node_args));
		i++;
	}
	return (node_args);
}

t_ast	*get_right_node_command(char **args, int index, t_mshell *mshell)
{
	t_ast	*node;
	char	**node_args;
	char	*cmd_path;

	node_args = get_right_node_args(args, index);
	if (node_args == NULL)
		return (NULL);
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

static char	**get_right_node_args(char **args, int index)
{
	int		i;
	char	**node_args;
	int		node_args_len;

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
		if (node_args[i] == NULL)
			return (free_split(node_args));
		i++;
	}
	return (node_args);
}

t_ast	*get_right_node_heredoc(char **args, int index)
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
