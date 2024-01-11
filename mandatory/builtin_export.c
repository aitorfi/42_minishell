/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:39:36 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/11 19:00:42 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	compare_lens(char *s1, char *s2)
{
	size_t len_to_use;

	len_to_use = ft_strlen(s1);
	if (ft_strlen(s2) > ft_strlen(s1))
		len_to_use = ft_strlen(s2);
	return (len_to_use);
}

void	sort_export(char **env_to_export)
{
	size_t	i;
	char	*temp;
	size_t	len_to_compare;

	i = 0;
	while (env_to_export[i] && env_to_export[i + 1])
	{
		len_to_compare = compare_lens(env_to_export[i], env_to_export[i + 1]);
		if (env_to_export[i + 1] && ft_strncmp(env_to_export[i + 1], env_to_export[i],
			len_to_compare) < 0)
		{
			temp = env_to_export[i];
			env_to_export[i] = env_to_export[i + 1];
			env_to_export[i + 1] = temp;
		}
		i++;
	}
}

int check_sort_export(char **env_to_export)
{
	size_t	i;
	size_t	len_to_compare;

	i = 0;
	len_to_compare = 0;
	while (env_to_export[i] && env_to_export[i + 1])
	{
		len_to_compare = compare_lens(env_to_export[i], env_to_export[i + 1]);
		if (env_to_export[i + 1] && ft_strncmp(env_to_export[i + 1], env_to_export[i],
			len_to_compare) < 0)
				return (1);
		i++; 
	}
	return (0);
}

static char	*do_export_NO_args(t_mshell *mini_data)
{
	size_t	i;
	char	**env_to_export;

	i = 0;
	while (mini_data->env_custom[i])
		i++;
	env_to_export = malloc(sizeof(char *) * (i + 1));
	if (env_to_export == NULL)
		return (ft_putstr_fd("Could not get environment to export", 2), NULL);
	i = 0;
	while (mini_data->env_custom[i])
	{
		env_to_export[i] = ft_strdup(mini_data->env_custom[i]);
		if (env_to_export[i] == NULL)
			return (ft_putstr_fd("Could not get environment to export", 2), NULL);
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
	char	*env_to_export;

	arg_valid = 1;
	env_to_export = NULL;
	if (!arguments[arg_valid])
	{
		env_to_export = do_export_NO_args(mini_data);
		
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
	return (0);
}
