/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:12:47 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/19 19:10:32 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	execute_builtin(t_ast *node, t_ast_node_type type, int *rfd, int *wfd, t_mshell *mshell)
{
	int	len;

	(void) rfd;
	(void) wfd;
	(void) type;
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
		return (do_exit(node->args));
	return (EXIT_FAILURE);
}
