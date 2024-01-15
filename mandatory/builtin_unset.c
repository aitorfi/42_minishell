/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:48:08 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/15 13:33:22 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	change_unset_env(t_mshell *mini_data, size_t pos)
{
	size_t	i;
	size_t	j;
	char	**new_env;

	i = 0;
	while (mini_data->env_custom[i])
		i++;
	new_env = malloc(sizeof(char *) * (i));
	if (new_env == NULL)
		return (ft_putstr_fd("could not update env", 2), 1);
	i = 0;
	j = 0;

	// a partir de aqui, sacar a otra funcion
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
	return (ft_free_env(mini_data->env_custom), mini_data->env_custom = new_env, 0);
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

static void	print_error_unset(char *arguments)
{
	ft_putstr_fd("minishell> unset `", 2);
	ft_putstr_fd(arguments, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	do_unset(t_mshell *mini_data, char **arguments)
{
	size_t	i;

	(void) mini_data;
	i = 1;
	if (!arguments[i])
		return (0);
	while (arguments[i])
	{
		if (check_export_args(arguments[i]))
		{
			print_error_unset(arguments[i]);
			i++;
		}
		if (exec_unset_env(mini_data, arguments[i]))
			return (1);
		i++;
	}
	return (0);
	
}

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
	arguments[1] = "pepe";
	arguments[2] = "_2=((()))";
	arguments[3] = "1";
	arguments[4] = "Zeta1=Hola";
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
	if (do_unset(&mini_data, arguments))
		return (1);
	printf("********************************************\n");
	do_export(&mini_data, arguments2);
	ft_free_env(mini_data.env_custom);
	//system("leaks a.out");
	return (0);
}
