/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:12:45 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/10 20:05:44 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_exec_update_env(t_mshell *mini_data, char *which, char *to_change)
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
	//printf("%s\n", to_change);
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
		if (ft_strncmp(env_to_get, envp[i], ft_strlen(env_to_get) - 1) == 0)
			break ;
		i++;
	}
	return (envp[i]);
}

static int do_cd_home(t_mshell *mini_data)
{
	char	*dir_to_save;
	char	*env_home;

	env_home = ft_get_env("HOME", mini_data->env_custom);
	if (env_home == NULL)
		return (ft_putstr_fd("cd: could not get HOME\n", 2), 1);
	env_home = ft_set_env(env_home);
	if (env_home == NULL)
		return (ft_putstr_fd("cd: could not set home", 2), 2);
	if (ft_update_env(env_home, mini_data, "PWD") == -1)
		return (ft_putstr_fd("cd: could not update env", 2), 3);
	dir_to_save = getcwd(NULL, 0); //tengo que liberar
	if (dir_to_save == NULL)
		return (ft_putstr_fd("cd: could not update env", 2), 3);
	if (ft_update_env(dir_to_save, mini_data, "OLDPWD") == -1)
		return (ft_putstr_fd("cd: could not update env", 2), 3);
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
	if (!ft_strncmp(arguments[i], ".", ft_strlen(arguments[i])))
		return (0);
	if (!ft_strncmp(arguments[i], "--", 3) 
	|| !ft_strncmp(arguments[i], "~", ft_strlen(arguments[i])))
		return (do_cd_home(mini_data));
	if (arguments[i] == NULL)
		return (do_cd_home(mini_data));
	cwd = getcwd(NULL, 0);
	if (!ft_strncmp(arguments[i], "..", ft_strlen(arguments[i])) 
	|| !ft_strncmp(arguments[i], "-", ft_strlen(arguments[i])))
	{
		arguments[i] = set_cd_special_case(cwd, arguments[i], mini_data);
		if (arguments[i] == NULL)
			return (ft_putstr_fd("cd: could not set especial case", 2), 1);
		free_b = 1;
	}
	free(cwd);
	return (do_cd_exec(cwd, mini_data, arguments[i], free_b));
}

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
	arguments[1] = "../libft";
	arguments[2] = NULL;
	mini_data.env_custom = do_env(envp, 0);
	/*while (mini_data.env_custom[i])
	{
		printf("%s\n", mini_data.env_custom[i]);
		i++;
	}*/
	i = 0;
	printf("********************************************************\n");
	do_cd(&mini_data, arguments);
	printf("********************************************************\n");
	/*while (mini_data.env_custom[i])
	{
		printf("%s\n", mini_data.env_custom[i]);
		i++;
	}*/
	cwd = getcwd(NULL, 0);
	printf("********************************************************\n");
	printf("cwd: %s\n", cwd);
	ft_free_env(mini_data.env_custom);
	return (0);
}
