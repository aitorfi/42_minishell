/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 11:43:23 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/07 13:56:00 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*is_operator(char *str)
{
	int		i;
	char	*operator;

	i = OPERATOR_MAX_LEN;
	while (i > 0)
	{
		operator = ft_substr(str, 0, i);
		if (operator == NULL)
			return (NULL);
		if (!ft_strncmp(operator, "<", i)
			|| !ft_strncmp(operator, "<<", i)
			|| !ft_strncmp(operator, ">", i)
			|| !ft_strncmp(operator, ">>", i)
			|| !ft_strncmp(operator, "|", i))
		{
			break ;
		}
		free(operator);
		i--;
	}
	if (i == 0)
		return (ft_strdup(""));
	return (operator);
}

t_operation	which_operator(char *operator)
{
	int	len;

	len = ft_strlen(operator);
	if (ft_strncmp(operator, "<", len))
		return (IN_REDIR_OP);
	if (ft_strncmp(operator, "<<", len))
		return (IN_REDIR_APPEND_OP);
	if (ft_strncmp(operator, ">", len))
		return (OUT_REDIR_OP);
	if (ft_strncmp(operator, ">>", len))
		return (OUT_REDIR_APPEND_OP);
	if (ft_strncmp(operator, "|", len))
		return (PIPE_OP);
	return (0);
}

void	*free_massive(void *ptr, ...)
{
	va_list	args;

	va_start(args, ptr);
	free(ptr);
	ptr = va_arg(args, void *);
	while (ptr)
	{
		free(ptr);
		ptr = va_arg(args, void *);
	}
	va_end(args);
	return (NULL);
}

void	*free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}
