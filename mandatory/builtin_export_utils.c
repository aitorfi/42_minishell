/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:00:04 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/12 19:55:34 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_export_env(t_mshell *mini_data, char *arguments, size_t pos)
{
	free(mini_data->env_custom[pos]);
	mini_data->env_custom[pos] = ft_strdup(arguments);
}

int	add_export_env(t_mshell *mini_data, char *arguments)
{
	size_t	i;
	char	**new_env;

	i = 0;
	while (mini_data->env_custom[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (new_env == NULL)
		return (ft_putstr_fd("could not update env", 2), 1);
	i = 0;
	while (mini_data->env_custom[i])
	{
		new_env[i] = ft_strdup(mini_data->env_custom[i]);
		i++;
	}
	new_env[i] = ft_strdup(arguments);
	new_env[++i] = NULL;
	ft_free_env(mini_data->env_custom);
	return (mini_data->env_custom = new_env, 0);
}

void	print_error_export(char *arguments)
{
	ft_putstr_fd("minishell> export `", 2);
	ft_putstr_fd(arguments, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	print_export(char **env_to_export)
{
	size_t	i;

	i = 0;
	while (env_to_export[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_export_fd(env_to_export[i], 1);
		write(1, "\n", 1);
		i++;
	}
}

size_t	compare_lens(char *s1, char *s2)
{
	size_t	len_to_use;

	len_to_use = ft_strlen(s1);
	if (ft_strlen(s2) > ft_strlen(s1))
		len_to_use = ft_strlen(s2);
	return (len_to_use);
}
