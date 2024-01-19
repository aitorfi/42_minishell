/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:54:26 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/19 18:43:20 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// NOTA: Este modulo imprime las variables de entorno que se han guardado
// en la memoria dinamica.
// NOTA: Devuelve un error en caso de que se llame al comando ENV antes
// de que n se hayan guardado las varibles en memoria dinamica.

int	execute_env(char **environment)
{
	size_t	i;

	if (environment == NULL)
		return (ft_putstr_fd("Environment not set", 2), 1);
	i = 0;
	while (environment[i])
	{
		if (ft_check_equal(environment[i]))
		{
			ft_putstr_fd(environment[i], 1);
			write(1, "\n", 1);
		}
		i++;
	}
	return (0);
}
/*
int	main(int argc, char **argv, char **envp)
{
	t_mshell	mini_data;
	//size_t		i;
	
	(void) argc;
	(void) argv;

	mini_data.env_custom = do_env_init(envp, 0);
	if (mini_data.env_custom == NULL)
		return (1);
	i = 0;
	while (mini_data.env_custom[i])
	{
		printf("%s\n", mini_data.env_custom[i]);
		i++;
	}
	if (execute_env(mini_data.env_custom))
		return (1);
	ft_free_env(mini_data.env_custom);
	return (0);
}*/
