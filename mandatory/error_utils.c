/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:55:54 by aitorfi           #+#    #+#             */
/*   Updated: 2024/02/01 20:14:16 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	notify_error(char *msg)
{
	perror(msg);
	return (EXIT_FAILURE);
}

void	*notify_error_ptr(char *msg)
{
	perror(msg);
	return (NULL);
}

void	*free_massive(void *ptr, ...)
{
	va_list	args;
	void	*arg_ptr;

	va_start(args, ptr);
	arg_ptr = va_arg(args, void *);
	while (arg_ptr)
	{
		free(arg_ptr);
		arg_ptr = va_arg(args, void *);
	}
	va_end(args);
	free(ptr);
	return (NULL);
}

int	free_massive_exit_failure(void *ptr, ...)
{
	va_list	args;
	void	*arg_ptr;

	va_start(args, ptr);
	arg_ptr = va_arg(args, void *);
	while (arg_ptr)
	{
		free(arg_ptr);
		arg_ptr = va_arg(args, void *);
	}
	va_end(args);
	free(ptr);
	return (EXIT_FAILURE);
}

void	*free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
	return (NULL);
}
