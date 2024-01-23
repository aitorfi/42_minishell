/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:23:44 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/20 14:24:45 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_unset_args(char *arguments)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(arguments[i]) && arguments[i] != '_')
		return (1);
	i++;
	while (arguments[i] && arguments[i] != '=')
	{
		if (!ft_isalnum(arguments[i]) && arguments[i] != '_')
			return (1);
		i++;
	}
	if (arguments[i] == '=')
		return (1);
	return (0);
}

void	print_error_unset(char *arguments)
{
	g_result = 1;
	ft_putstr_fd("minishell> unset `", 2);
	ft_putstr_fd(arguments, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}
