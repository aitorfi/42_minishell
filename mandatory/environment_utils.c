/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:01:50 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/20 11:22:43 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_env(char **env_custom)
{
	size_t	i;

	i = 0;
	while (env_custom[i])
	{
		free(env_custom[i]);
		i++;
	}
	free(env_custom);
}

int	ft_exec_update_env(t_mshell *mini_data, char *which, char *to_change)
{
	size_t	i;
	char	*temp;

	i = 0;
	while (mini_data->env_custom[i])
	{
		if (!ft_strncmp(which, mini_data->env_custom[i], ft_strlen(which) - 1))
		{
			temp = mini_data->env_custom[i];
			mini_data->env_custom[i] = to_change;
			free(temp);
			return (0);
		}
		i++;
	}
	return (-1);
}

int	ft_update_env(char	*new_content, t_mshell *mini_data, char *which)
{
	char	*set_new;
	char	*to_change;
	char	*temp;

	set_new = ft_strdup(new_content);
	if (set_new == NULL)
		return (-1);
	temp = ft_strjoin(which, "=");
	if (temp == NULL)
		return (-1);
	to_change = ft_strjoin(temp, set_new);
	if (to_change == NULL)
		return (-1);
	free(temp);
	if (ft_exec_update_env(mini_data, which, to_change) == -1)
		return (-1);
	return (free(set_new), 0);
}

char	*ft_set_env(char *env_to_set)
{
	size_t	i;

	i = 0;
	while (env_to_set[i] && env_to_set[i] != '=')
		i++;
	if (env_to_set[i] == '=')
		i++;
	return (&env_to_set[i]);
}

char	*ft_get_env(char *env_to_get, char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(env_to_get, envp[i], ft_strlen(env_to_get)) == 0
			&& (envp[i][ft_strlen(env_to_get)] == '='
			|| envp[i][ft_strlen(env_to_get)] == 0))
			break ;
		i++;
	}
	return (envp[i]);
}
