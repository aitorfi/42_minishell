/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:12:45 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/20 11:22:02 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	do_cd_exec(char *cwd_be, t_mshell *mini_data,
char *arguments, int free_b)
{
	char	*cwd_af;

	if (chdir(arguments))
	{
		free(arguments);
		return (perror("cd: could not change to directory"), 4);
	}
	if (ft_update_env(cwd_be, mini_data, "OLDPWD") == -1)
		return (ft_putstr_fd("cd: could not update env\n", 2), 3);
	cwd_af = getcwd(NULL, 0);
	if (cwd_af == NULL)
		return (perror("cd: could not update env"), 3);
	if (ft_update_env(cwd_af, mini_data, "PWD") == -1)
		return (ft_putstr_fd("cd: could not update env\n", 2), 3);
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

static char	*set_cd_special_case(char *cwd, char *arguments,
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

static int	do_cd_home(t_mshell *mini_data)
{
	char	*dir_to_save;
	char	*env_home;

	env_home = ft_get_env("HOME", mini_data->env_custom);
	if (env_home == NULL)
		return (ft_putstr_fd("cd: could not get HOME\n", 2), 1);
	env_home = ft_set_env(env_home);
	if (env_home == NULL)
		return (ft_putstr_fd("cd: could not set home\n", 2), 2);
	if (ft_update_env(env_home, mini_data, "PWD") == -1)
		return (ft_putstr_fd("cd: could not update env\n", 2), 3);
	dir_to_save = getcwd(NULL, 0);
	if (dir_to_save == NULL)
		return (perror("cd: could not update env"), 3);
	if (ft_update_env(dir_to_save, mini_data, "OLDPWD") == -1)
		return (ft_putstr_fd("cd: could not update env\n", 2), 3);
	if (chdir(env_home))
		return (perror("cd: could not change to home"), 4);
	free(dir_to_save);
	return (0);
}

int	do_cd(t_mshell *mini_data, char **arguments)
{
	size_t	i;
	char	*cwd;
	int		free_b;

	i = 1;
	free_b = 0;
	if (arguments[i] == NULL || !ft_strncmp(arguments[i], "--", 3)
		|| !ft_strncmp(arguments[i], "~", ft_strlen(arguments[i])))
		return (do_cd_home(mini_data));
	if (!ft_strncmp(arguments[i], ".", ft_strlen(arguments[i])))
		return (0);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (perror("cd: could not update env"), 3);
	if (!ft_strncmp(arguments[i], "..", ft_strlen(arguments[i]))
		|| !ft_strncmp(arguments[i], "-", ft_strlen(arguments[i])))
	{
		arguments[i] = set_cd_special_case(cwd, arguments[i], mini_data);
		if (arguments[i] == NULL)
			return (1);
		free_b = 1;
	}
	if (do_cd_exec(cwd, mini_data, arguments[i], free_b))
		return (free(cwd), 1);
	return (free(cwd), 0);
}
/*
int	main(int argc, char **argv, char **envp)
{
	t_mshell	mini_data;
	char		*arguments[3];
	size_t		i;
	char		*cwd;

	i = 0;
	(void) argc;
	(void) argv;
	arguments[0] = "cd";
	arguments[1] = "..";
	arguments[2] = NULL;
	mini_data.env_custom = do_env_init(envp, 1);
	//while (mini_data.env_custom[i])
	//{
	//	printf("%s\n", mini_data.env_custom[i]);
	//	i++;
	//}
	i = 0;
	printf("****************DESPUES DEL CD********************\n");
	do_cd(&mini_data, arguments);
	printf("********************************************************\n");
	//while (mini_data.env_custom[i])
	//{
	//	printf("%s\n", mini_data.env_custom[i]);
	//	i++;
	//}
	cwd = getcwd(NULL, 0);
	printf("********************************************************\n");
	printf("cwd: %s\n", cwd);
	printf("********************************************************\n");
	free(cwd);
	ft_free_env(mini_data.env_custom);
	return (0);
}*/
