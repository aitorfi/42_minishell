/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:01:50 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/10 20:04:29 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	do_cd_exec(char *cwd_be, t_mshell *mini_data, char *arguments, int free_b)
{
	char	*cwd_af;

	printf("old: %s\n", cwd_be);
	if (chdir(arguments))
		return (perror("cd: could not change to directory"), 4);
	cwd_af = getcwd(NULL, 0);
	if (cwd_af == NULL)
		return (ft_putstr_fd("cd: could not update env", 2), 3);
	printf("new: %s\n", cwd_af);
	if (ft_update_env(cwd_be, mini_data, "OLDPWD") == -1)
		return (ft_putstr_fd("cd: could not update env", 2), 3);
	if (ft_update_env(cwd_af, mini_data, "PWD") == -1)
		return (ft_putstr_fd("cd: could not update env", 2), 3);
	if (free_b)
		free(arguments);
	free(cwd_af);
	return (0);
}

static char	*set_cd_one_up(char *cwd)
{
	size_t	i;
	char	*dir_one_up;

	i = 0;
	while (cwd[i])
		i++;
	i = i - 1;
	while (cwd[i] != '/' && cwd[i])
		i--;
	dir_one_up = ft_substr(cwd, 0, ft_strlen(cwd) - ft_strlen(&cwd[i]));
	if (dir_one_up == NULL)
		return (NULL);
	return (dir_one_up);
}	

char	*set_cd_special_case(char *cwd, char *arguments, t_mshell *mini_data)
{
	char	*dir_to_go;

	if (!ft_strncmp(arguments, "..", ft_strlen(arguments)))
	{
		dir_to_go = set_cd_one_up(cwd);
		if (dir_to_go == NULL)
			return (NULL);
	}
	if (!ft_strncmp(arguments, "-", ft_strlen(arguments)))
	{
		dir_to_go = ft_get_env("OLDPWD", mini_data->env_custom);
		if (dir_to_go == NULL)
			return (ft_putstr_fd("cd: could not get OLDPWD\n", 2), NULL);
		dir_to_go = ft_set_env(dir_to_go);
		if (dir_to_go == NULL)
			return (ft_putstr_fd("cd: could not set OLDPWD\n", 2), NULL);
		dir_to_go = ft_strdup(dir_to_go);
		if (dir_to_go == NULL)
			return (ft_putstr_fd("cd: error getting OLPWD value", 2), NULL);
		ft_putstr_fd(dir_to_go, 1);
		write(1, "\n", 1);
	}
	return (dir_to_go);
}
