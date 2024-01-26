/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:27:13 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/26 17:34:25 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	do_exit_number(char **arguments, int is_main_process)
{
	size_t	i;

	i = 1;
	if (arguments[i + 1])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	g_result = ft_atoi_exit(arguments[i], is_main_process);
	if (g_result != EXIT_FAILURE && is_main_process)
		ft_putstr_fd("exit\n", 2);
	return (g_result);
}

static int	do_exit_letter(char **arguments, int is_main_process)
{
	size_t	i;

	i = 1;
	if (is_number(arguments[i]) && !is_number(arguments[i + 1]))
	{
		if (is_main_process)
			ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	while (arguments[i])
	{
		if (!is_number(arguments[i]))
			break ;
		i++;
	}
	if (is_main_process)
		ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arguments[i], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (EXIT_FAILURE);
}

int	do_exit(char **arguments, int is_main_process)
{
	size_t	i;
	int		flag;

	i = 1;
	if (!arguments[i])
	{
		if (is_main_process)
			write(1, "exit\n", 5);
		return (g_result);
	}
	check_exit_args(arguments, &flag);
	if (flag == 1)
		return (do_exit_number(arguments, is_main_process));
	else
		return (do_exit_letter(arguments, is_main_process));
}

int	can_do_exit(char **arguments)
{
	size_t	i;
	int		arg1_isnumber;

	if (!arguments[1] || !arguments[2])
		return (1);
	i = 0;
	while (ft_isdigit(arguments[1][i]))
		i++;
	arg1_isnumber = (i == ft_strlen(arguments[1]));
	if (arg1_isnumber)
		return (0);
	else
		return (1);
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