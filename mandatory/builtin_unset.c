/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:48:08 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/26 09:05:06 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	make_change_unset(t_mshell *mini_data, size_t pos, char **new_env)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	while (mini_data->env_custom[j])
	{
		if (j != pos)
		{
			new_env[i] = ft_strdup(mini_data->env_custom[j]);
			if (new_env[i] == NULL)
				return (ft_putstr_fd("could not update env", 2), 1);
			i++;
			j++;
		}
		else
			j++;
	}
	new_env[i] = NULL;
	ft_free_env(mini_data->env_custom);
	mini_data->env_custom = new_env;
	return (0);
}

static int	change_unset_env(t_mshell *mini_data, size_t pos)
{
	size_t	i;
	char	**new_env;

	i = 0;
	while (mini_data->env_custom[i])
		i++;
	new_env = malloc(sizeof(char *) * (i));
	if (new_env == NULL)
		return (ft_putstr_fd("could not update env", 2), 1);
	if (make_change_unset(mini_data, pos, new_env))
		return (1);
	return (0);
}

static int	exec_unset_env(t_mshell *mini_data, char *arguments)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (arguments[j] && arguments[j] != '=')
		j++;
	i = 0;
	while (mini_data->env_custom[i])
	{
		if (!ft_strncmp(mini_data->env_custom[i], arguments, j)
			&& (mini_data->env_custom[i][j] == 0
			|| mini_data->env_custom[i][j] == '='))
		{
			if (change_unset_env(mini_data, i))
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (0);
}

int	do_unset(t_mshell *mini_data, char **arguments)
{
	size_t	i;

	i = 1;
	if (!arguments[i])
		return (0);
	while (arguments[i])
	{
		if (check_unset_args(arguments[i]))
			print_error_unset(arguments[i]);
		else
		{
			if (exec_unset_env(mini_data, arguments[i]))
				return (1);
		}
		i++;
	}
	return (0);
}
/*
int	main(int argc, char **argv, char **envp)
{
	t_mshell	mini_data;
	char		*arguments[8];
	size_t		i;
	char		*arguments2[2];
	char		*arguments3[5];
	
	(void) argc;
	//i = 0;
	//while (argv[i])
	//{
	//	printf("argv: %s\n", argv[i]);
	//	i++;
	//}
	(void) argv;
	arguments[0] = "export";
	arguments[1] = "pepon=";
	arguments[2] = "_2=((()))";
	arguments[3] = "Zeta1";
	arguments[4] = "Zeta1=holaaaaa";
	arguments[5] = "Zeta2";
	arguments[6] = "Zeta2=pepe";
	arguments[7] = NULL;
	mini_data.env_custom = do_env_init(envp, 0);
	//i = 0;
	//while (mini_data.env_custom[i])
	//{
	//	printf("%s\n", mini_data.env_custom[i]);
	//	i++;
	//}
	printf("********************************************\n");
	if (mini_data.env_custom == NULL)
		return (1);
	if (do_export(&mini_data, arguments))
		return (1);
	i = 0;
	//while (mini_data.env_custom[i])
	//{
	//	printf("%s\n", mini_data.env_custom[i]);
	//	i++;
	//}
	arguments2[0] = "export";
	arguments2[1] = NULL;
	printf("********************************************\n");
	do_export(&mini_data, arguments2);
	printf("********************************************\n");
	//execute_env(mini_data.env_custom);
	arguments3[0] = "unset";
	arguments3[1] = "2";
	arguments3[2] = "Zeta1=holaa";
	arguments3[3] = "_2";
	arguments3[4] = NULL;
	if (do_unset(&mini_data, arguments3))
		return (1);
	printf("hola********************************************\n");
	do_export(&mini_data, arguments2);
	ft_free_env(mini_data.env_custom);
	//system("leaks a.out");
	return (0);
}
*/
