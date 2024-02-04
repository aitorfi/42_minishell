/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 11:43:23 by afidalgo          #+#    #+#             */
/*   Updated: 2024/02/04 10:19:10 by afidalgo         ###   ########.fr       */
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
