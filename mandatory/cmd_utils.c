/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:48:07 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/19 18:48:53 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_full_cmd_from_path(char **cmd_paths, char *cmd);

char	*append_path_to_cmd(char **envp, char *cmd)
{
	int		i;
	char	**cmd_paths;
	char	*full_path;

	if (ft_strchr(cmd, '/') || is_builtin(cmd))
		return (ft_strdup(cmd));
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
		return (ft_strdup(cmd));
	cmd_paths = ft_split(envp[i] + 5, ':');
	if (cmd_paths == NULL)
		return (NULL);
	full_path = get_full_cmd_from_path(cmd_paths, cmd);
	free_split(cmd_paths);
	return (full_path);
}

static char	*get_full_cmd_from_path(char **cmd_paths, char *cmd)
{
	char	*full_cmd;
	char	*path_tmp;
	int		i;

	i = 0;
	while (cmd_paths[i])
	{
		if (cmd_paths[i][ft_strlen(cmd_paths[i]) - 1] == '/')
			full_cmd = ft_strjoin(cmd_paths[i], cmd);
		else
		{
			path_tmp = ft_strjoin(cmd_paths[i], "/");
			if (path_tmp == NULL)
				return (NULL);
			full_cmd = ft_strjoin(path_tmp, cmd);
			free(path_tmp);
			if (full_cmd == NULL)
				return (NULL);
		}
		if (access(full_cmd, F_OK) == 0)
			return (full_cmd);
		free(full_cmd);
		i++;
	}
	return (ft_strdup(cmd));
}
