/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:39:36 by alvicina          #+#    #+#             */
/*   Updated: 2024/02/02 11:43:07 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	exec_export_env(t_mshell *mini_data, char *arguments)
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
			if (change_export_env(mini_data, arguments, i))
				return (1);
			else
				return (0);
		}
		i++;
	}
	if (add_export_env(mini_data, arguments))
		return (1);
	return (0);
}

int	check_export_args(char *arguments)
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
	return (0);
}

static int	do_export_args(t_mshell *mini_data, char **arguments)
{
	size_t	i;

	i = 1;
	while (arguments[i])
	{
		if (check_export_args(arguments[i]))
			print_error_export(arguments[i]);
		else
		{
			if (exec_export_env(mini_data, arguments[i]))
				return (1);
		}
		i++;
	}
	return (0);
}

static char	**do_export_no_args(t_mshell *mini_data)
{
	size_t	i;
	char	**env_to_export;

	i = 0;
	while (mini_data->env_custom[i])
		i++;
	env_to_export = malloc(sizeof(char *) * (i + 1));
	if (env_to_export == NULL)
		return (ft_putstr_fd("Could not get env to export", 2), NULL);
	i = 0;
	while (mini_data->env_custom[i])
	{
		env_to_export[i] = ft_strdup(mini_data->env_custom[i]);
		if (env_to_export[i] == NULL)
			return (ft_putstr_fd("Could not get env to export", 2), NULL);
		i++;
	}
	env_to_export[i] = NULL;
	while (check_sort_export(env_to_export))
		sort_export(env_to_export);
	return (env_to_export);
}

int	do_export(t_mshell *mini_data, char **arguments)
{
	int		arg_valid;
	char	**env_to_export;

	arg_valid = 1;
	env_to_export = NULL;
	if (!arguments[arg_valid])
	{
		env_to_export = do_export_no_args(mini_data);
		if (env_to_export == NULL)
			return (1);
		print_export(env_to_export);
		ft_free_env(env_to_export);
		return (0);
	}
	else
	{
		if (do_export_args(mini_data, arguments))
			return (1);
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
	
	(void) argc;
	//i = 0;
	//while (argv[i])
	//{
	//	printf("argv: %s\n", argv[i]);
	//	i++;
	//}
	(void) argv;
	arguments[0] = "export";
	arguments[1] = "1";
	arguments[2] = "2";
	arguments[3] = "3";
	arguments[4] = "4";
	arguments[5] = "5";
	arguments[6] = "6";
	arguments[7] = NULL;
	mini_data.env_custom = do_env_init(envp, 0);
	i = 0;
	while (mini_data.env_custom[i])
	{
		printf("%s\n", mini_data.env_custom[i]);
		i++;
	}
	printf("********************************************\n");
	if (mini_data.env_custom == NULL)
		return (1);
	if (do_export(&mini_data, arguments))
		return (1);
	i = 0;
	while (mini_data.env_custom[i])
	{
		printf("%s\n", mini_data.env_custom[i]);
		i++;
	}
	arguments2[0] = "export";
	arguments2[1] = NULL;
	printf("********************************************\n");
	do_export(&mini_data, arguments2);
	printf("********************************************\n");
	execute_env(mini_data.env_custom);
	ft_free_env(mini_data.env_custom);
	//system("leaks a.out");
	return (0);
}*/
