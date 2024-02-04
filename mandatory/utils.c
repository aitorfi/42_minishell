/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 11:43:23 by afidalgo          #+#    #+#             */
/*   Updated: 2024/02/04 13:46:57 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_operation	which_operator(char *operator)
{
	int	len;

	len = ft_strlen(operator);
	if (!ft_strncmp(operator, "<", max_of(len, 1)))
		return (IN_REDIR_OP);
	if (!ft_strncmp(operator, "<<", max_of(len, 2)))
		return (IN_REDIR_APPEND_OP);
	if (!ft_strncmp(operator, ">", max_of(len, 1)))
		return (OUT_REDIR_OP);
	if (!ft_strncmp(operator, ">>", max_of(len, 2)))
		return (OUT_REDIR_APPEND_OP);
	if (!ft_strncmp(operator, "|", max_of(len, 1)))
		return (PIPE_OP);
	return (0);
}

char	*which_operator_str(t_operation operator)
{
	if (operator == IN_REDIR_OP)
		return ("IN_REDIR_OP (<)");
	if (operator == IN_REDIR_APPEND_OP)
		return ("IN_REDIR_APPEND_OP (<<)");
	if (operator == OUT_REDIR_OP)
		return ("OUT_REDIR_OP (>)");
	if (operator == OUT_REDIR_APPEND_OP)
		return ("OUT_REDIR_APPEND_OP (>>)");
	if (operator == PIPE_OP)
		return ("PIPE_OP (|)");
	if (operator == COMMAND_OP)
		return ("COMMAND_OP");
	if (operator == FILE_OP)
		return ("FILE_OP");
	return ("");
}

int	max_of(int num1, int num2)
{
	if (num1 > num2)
		return (num1);
	return (num2);
}

int	split_len(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	is_terminating_cmd(t_ast **ast)
{
	int	path_len;

	if (!ast[0]->left && !ast[0]->right && ast[0]->operation == COMMAND_OP)
	{
		path_len = ft_strlen(ast[0]->path);
		if (!ft_strncmp(ast[0]->path, "exit", max_of(path_len, 4))
			&& can_do_exit(ast[0]->args))
		{
			return (1);
		}
	}
	return (0);
}
