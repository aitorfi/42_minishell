/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:37:33 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/26 17:13:52 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	do_exit_atoi(char *arguments, int is_main_process)
{
	g_result = 1;
	if (is_main_process)
		ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arguments, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (EXIT_FAILURE);
}

int	ft_atoi_exit(char *str, int is_main_process)
{
	int					i;
	int					neg;
	unsigned long int	num_atoi;	

	i = 0;
	neg = 1;
	num_atoi = 0;
	while (str[i] != 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		num_atoi = num_atoi * 10 + str[i] - 48;
		if (num_atoi > 0x7fffffffffffffff)
			return (do_exit_atoi(str, is_main_process));
		i++;
	}
	return ((num_atoi * neg) % 256);
}

void	check_exit_args(char **arguments, int *flag)
{
	size_t	i;

	i = 1;
	while (arguments[i])
	{
		if (is_number(arguments[i]))
		{
			i++;
			*flag = 1;
		}
		else
		{
			*flag = 0;
			break ;
		}
	}
}

int	is_number(char *arguments)
{
	size_t	i;

	i = 0;
	while (arguments[i])
	{
		if (!ft_isdigit(arguments[i]))
			return (0);
		i++;
	}
	return (1);
}
