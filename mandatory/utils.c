/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 11:43:23 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/09 18:42:13 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_operator(char *str)
{
	int	len;

	len = ft_strlen(str);
	return (!ft_strncmp(str, "<", len)
		|| !ft_strncmp(str, "<<", len)
		|| !ft_strncmp(str, ">", len)
		|| !ft_strncmp(str, ">>", len)
		|| !ft_strncmp(str, "|", len));
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
