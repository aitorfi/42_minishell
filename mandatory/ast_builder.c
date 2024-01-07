/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:59:30 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/07 14:17:18 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_ast	*create_op_node(t_ast **ast, char *line, int index, char *op);
static t_ast	*get_left_node(char *line, int end);
static int		get_left_command_start(char *line, int end);
static t_ast	*get_right_node(char *line, t_operation op);

t_ast	**build_ast(char *line)
{
	t_ast	**ast;
	int		i;
	char	*operator;

	ast = malloc(sizeof(t_ast *));
	if (ast == NULL)
		return (NULL);
	i = 0;
	while (line[i])
	{
		//? Hay que validar que el operador este rodeado de espacios?
		operator = is_operator(&line[i]);
		if (operator == NULL)
			return (free_ast(ast));
		if (operator[0] != '\0')
		{
			if (create_op_node(ast, line, i, operator) == NULL)
				return (free_ast(ast));
			i += ft_strlen(operator) - 1;
		}
		free(operator);
		i++;
	}
	return (ast);
}

static t_ast	*create_op_node(t_ast **ast, char *line, int index, char *op)
{
	t_ast	*node;

	node = new_node(which_operator(op), NULL, NULL);
	if (node == NULL)
		return (NULL);
	if (ast[0])
		node->left = ast[0];
	else
		node->left = get_left_node(ft_strdup(line), index);
	node->right = get_right_node(&line[index + ft_strlen(op)], node->operation);
	ast[0] = node;
	return (node);
}

static t_ast	*get_left_node(char *line, int end)
{
	t_ast	*node;
	char	*command;
	char	**args;
	int		start;

	start = get_left_command_start(line, end);
	if (start == -1)
		return (free_massive(line));
	command = ft_substr(line, start, end);
	if (command == NULL)
		return (free_massive(line));
	args = ft_split(command, ' ');
	if (args == NULL)
		return (free_massive(line, command));
	node = new_node(COMMAND_OP, args[0], args);
	if (node == NULL)
	{
		free_split(args);
		return (free_massive(line, command));
	}
	free_massive(line, command);
	return (node);
}

static int	get_left_command_start(char *line, int end)
{
	int		i;
	char	*operator;
	int		start;

	line[end] = '\0';
	i = 0;
	start = 0;
	while (line[i])
	{
		operator = is_operator(&line[i]);
		if (operator == NULL)
			return (-1);
		if (operator[0])
			start = i;
		free(operator);
		i++;
	}
	return (start);
}

static t_ast	*get_right_node(char *line, t_operation op)
{
	int	i;
	char	*operator;
	char	*command;
	t_ast	*node;

	i = 0;
	while (line[i])
	{
		operator = is_operator(&line[i]);
		if (operator == NULL)
			return (NULL);
		if (operator[0])
		{
			free(operator);
			break ;
		}
		free(operator);
		i++;
	}
	command = ft_substr(line, 0, i);
	if (command == NULL)
		return (NULL);
	if (op == OUT_REDIR_APPEND_OP || op == OUT_REDIR_OP)
		node = new_node(FILE_OP, command, NULL);
	else
		node = new_command_node(command);
	if (node == NULL)
		return (free_massive(command));
	if (op != OUT_REDIR_APPEND_OP && op != OUT_REDIR_OP)
		free(command);
	return (node);
}
