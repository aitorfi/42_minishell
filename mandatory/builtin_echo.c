/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:38:10 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/09 12:29:59 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_check_option(char *option)
{
	size_t	i;

	i = 0;
	if (option[i] != '-')
		return (0);
	i++;
	if (option[i] != 'n')
		return (0);
	return (1);
}

int	do_echo(char **arguments)
{
	size_t	i;
	size_t	option;
	int		option_exist;

	i = 1;
	option = 0;
	option_exist = ft_check_option(arguments[i]);
	if (arguments[i] != NULL && option_exist)
	{
		option++;
		i++;
	}
	while (arguments[i])
	{
		ft_putstr_fd(arguments[i], 1);
		if (arguments[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (option == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
/*
int	main(void)
{
	char	*cmd[5];
//	size_t	i;
	
	cmd[0] = "echo";
	cmd[1] = "pedro";
	cmd[2] = "aita";
	cmd[3] = "pepe";
	cmd[4] = NULL;
//	i = 0;
//	while (cmd[i])
//	{
//		printf("%s\n", cmd[i]);
//		i++;
//	}
	do_echo(cmd);
	return (0);
}*/
