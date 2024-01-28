/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:48:07 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/27 12:50:44 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_full_cmd_from_path(char **envp, char *cmd);
static char	*get_full_cmd_from_split_path(char **cmd_paths, char *cmd);

char	*append_path_to_cmd(char **envp, char *cmd)
{
	char	*full_path;

	if (ft_strchr(cmd, '/') || is_builtin(cmd))
		full_path = ft_strdup(cmd);
	else
		full_path = get_full_cmd_from_path(envp, cmd);
	if (full_path == NULL)
		perror("Error al obtener el path completo del comando");
	return (full_path);
}

static char	*get_full_cmd_from_path(char **envp, char *cmd)
{
	int		i;
	char	**cmd_paths;
	char	*full_path;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL)
	{
		full_path = ft_strdup(cmd);
	}
	else
	{
		cmd_paths = ft_split(envp[i] + 5, ':');
		if (cmd_paths == NULL)
			return (NULL);
		full_path = get_full_cmd_from_split_path(cmd_paths, cmd);
		free_split(cmd_paths);
	}
	return (full_path);
}

static char	*get_full_cmd_from_split_path(char **cmd_paths, char *cmd)
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

int	is_builtin(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	return (!ft_strncmp(cmd, "cd", len)
		|| !ft_strncmp(cmd, "echo", len)
		|| !ft_strncmp(cmd, "env", len)
		|| !ft_strncmp(cmd, "export", len)
		|| !ft_strncmp(cmd, "pwd", len)
		|| !ft_strncmp(cmd, "unset", len)
		|| !ft_strncmp(cmd, "exit", len)
	);
}

int	execute_builtin(t_ast *node, t_mshell *mshell, int is_main_process)
{
	int	len;

	len = ft_strlen(node->path);
	if (!ft_strncmp(node->path, "cd", len))
		return (do_cd(mshell, node->args));
	if (!ft_strncmp(node->path, "echo", len))
		return (do_echo(node->args));
	if (!ft_strncmp(node->path, "env", len))
		return (execute_env(mshell->env_custom));
	if (!ft_strncmp(node->path, "export", len))
		return (do_export(mshell, node->args));
	if (!ft_strncmp(node->path, "pwd", len))
		return (do_pwd());
	if (!ft_strncmp(node->path, "unset", len))
		return (do_unset(mshell, node->args));
	if (!ft_strncmp(node->path, "exit", len))
		return (do_exit(node->args, is_main_process));
	return (EXIT_FAILURE);
}
