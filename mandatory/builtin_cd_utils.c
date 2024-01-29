/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:06:07 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/29 19:01:10 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*set_cd_one_up(char *cwd)
{
	size_t	i;
	char	*dir_one_up;

	i = 0;
	while (cwd[i])
		i++;
	i = i - 1;
	while (cwd[i] != '/' && cwd[i])
		i--;
	dir_one_up = ft_substr(cwd, 0, ft_strlen(cwd) - ft_strlen(&cwd[i + 1]));
	if (dir_one_up == NULL)
		return (NULL);
	return (dir_one_up);
}

char	*set_cd_special_case(char *cwd, char *arguments,
t_mshell *mini_data)
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
		if (*dir_to_go == 0)
			return (ft_putstr_fd("cd: OLDPWD not set\n", 2), NULL);
		dir_to_go = ft_strdup(dir_to_go);
		if (dir_to_go == NULL)
			return (ft_putstr_fd("cd: error getting OLPWD value\n", 2), NULL);
		ft_putstr_fd(dir_to_go, 1);
		write(1, "\n", 1);
	}
	return (dir_to_go);
}
