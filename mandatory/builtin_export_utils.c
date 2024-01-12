/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:00:04 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/12 11:47:50 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		ft_putstr_fd(env_to_export[i], 1);
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

void	sort_export(char **env_to_export)
{
	size_t	i;
	char	*temp;
	size_t	len_to_compare;

	i = 0;
	while (env_to_export[i] && env_to_export[i + 1])
	{
		len_to_compare = compare_lens(env_to_export[i], env_to_export[i + 1]);
		if (env_to_export[i + 1] && ft_strncmp(env_to_export[i + 1],
				env_to_export[i], len_to_compare) < 0)
		{
			temp = env_to_export[i];
			env_to_export[i] = env_to_export[i + 1];
			env_to_export[i + 1] = temp;
		}
		i++;
	}
}

int	check_sort_export(char **env_to_export)
{
	size_t	i;
	size_t	len_to_compare;

	i = 0;
	len_to_compare = 0;
	while (env_to_export[i] && env_to_export[i + 1])
	{
		len_to_compare = compare_lens(env_to_export[i], env_to_export[i + 1]);
		if (env_to_export[i + 1] && ft_strncmp(env_to_export[i + 1],
				env_to_export[i], len_to_compare) < 0)
			return (1);
		i++;
	}
	return (0);
}
