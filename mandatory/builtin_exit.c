/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:27:13 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/17 09:43:13 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	do_exit_number(char **arguments)
{
	size_t	i;

	i = 1;
	if (arguments[i + 1])
	{
		g_result = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	g_result = ft_atoi_exit(arguments[i]);
	ft_putstr_fd("exit\n", 2);
	exit(g_result); // antes del exit hay que liberar todo;
}

static void	do_exit_letter(char **arguments)
{
	size_t	i;

	i = 1;
	if (is_number(arguments[i]) && !is_number(arguments[i + 1]))
	{
		g_result = 1;
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	while (arguments[i])
	{
		if (!is_number(arguments[i]))
			break ;
		i++;
	}
	g_result = 1;
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arguments[i], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(g_result); // antes del exit hay que liberar todo;
}

int	do_exit(char **arguments)
{
	size_t	i;
	int		flag;

	i = 1;
	if (!arguments[i])
	{
		write(1, "exit\n", 5);
		exit(g_result); //antes del exit hay que liberar TODO;
	}
	check_exit_args(arguments, &flag);
	if (flag == 1)
		do_exit_number(arguments);
	else
		do_exit_letter(arguments);
	return (0);
}
/*
int	main(void)
{
	char	*arguments[4];

	g_result = 2;
	arguments[0] = "exit";
	arguments[1] = "99999999999999999999999999999999999
	99999999999999999999999999999999999999999";
	arguments[2] = NULL;
	arguments[3] = NULL;
	do_exit(arguments);
	return (0);
}
*/