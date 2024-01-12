/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 11:43:23 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/12 18:24:54 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_operation	which_operator(char *operator)
{
	int	len;

	len = ft_strlen(operator);
	if (!ft_strncmp(operator, "<", len))
		return (IN_REDIR_OP);
	if (!ft_strncmp(operator, "<<", len))
		return (IN_REDIR_APPEND_OP);
	if (!ft_strncmp(operator, ">", len))
		return (OUT_REDIR_OP);
	if (!ft_strncmp(operator, ">>", len))
		return (OUT_REDIR_APPEND_OP);
	if (!ft_strncmp(operator, "|", len))
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

char	*create_file(char *path, char *content)
{
	int	fd;

	fd = open(path, O_RDWR | O_CREAT, 0000644);
	if (fd == -1)
	{
		perror("Error");
		return (NULL);
	}
	if (write(fd, content, ft_strlen(content)) == -1)
	{
		perror("Error");
		close(fd);
		return (NULL);
	}
	close(fd);
	return (path);
}
