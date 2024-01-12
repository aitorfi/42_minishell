/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:39:36 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/12 09:25:29 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	//else
	//	do_export_args(mini_data, arguments[arg_valid]);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_mshell	mini_data;
	char		*arguments[4];
	//size_t		i;
	
	(void) argc;
	(void) argv;
	arguments[0] = "export";
	arguments[1] = NULL;
	arguments[2] = "Hola";
	arguments[3] = NULL;
	mini_data.env_custom = do_env_init(envp, 0);
	//i = 0;
	/*while (mini_data.env_custom[i])
	{
		printf("%s\n", mini_data.env_custom[i]);
		i++;
	}*/
	//printf("********************************************\n");
	if (mini_data.env_custom == NULL)
		return (1);
	if (do_export(&mini_data, arguments))
		return (1);
	ft_free_env(mini_data.env_custom);
	//system("leaks a.out");
	return (0);
}
