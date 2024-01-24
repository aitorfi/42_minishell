/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:36:22 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/24 11:16:42 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**exec_expand_simple(char *dolar, char **ast,
t_mshell *mini_data, size_t pos)
{
	char	*temp;

	temp = ft_get_env(dolar, mini_data->env_custom);
	if (temp == NULL)
	{
		temp = ft_strdup("");
		if (temp == NULL)
			return (perror("malloc error while expanding $"), NULL);
	}
	else
	{
		temp = ft_set_env(temp);
		temp = ft_strdup(temp);
		if (temp == NULL)
			return (perror("malloc error while expanding $"), NULL);
	}
	free(ast[pos]);
	ast[pos] = temp;
	return (ast);
}

char	*search_expand(char *to_expand, t_mshell *mini_data)
{
	char	*temp;

	temp = ft_get_env(to_expand, mini_data->env_custom);
	if (temp == NULL)
	{
		temp = ft_strdup("");
		if (temp == NULL)
			return (perror("malloc error while expanding $"), NULL);
	}
	else
	{
		temp = ft_set_env(temp);
		temp = ft_strdup(temp);
		if (temp == NULL)
			return (perror("malloc error while expanding $"), NULL);
	}
	return (temp);
}

void	d_expand_init(t_expand *d)
{
	d->i = 0;
	d->j = 0;
	d->flag = 0;
	d->keep = NULL;
	d->result = 0;
	d->search = NULL;
	d->first = NULL;
	d->second = NULL;
	d->temp = NULL;
	d->to_expand = NULL;
}

char	*check_dollar(char *ret)
{
	size_t	i;

	i = 0;
	while (ret[i])
	{
		if (ret[i] == '$')
		{
			i++;
			return (&ret[i]);
		}
		i++;
	}
	return (NULL);
}

int	check_expand(char *ret)
{
	if (ret[0] == '\'')
		return (0);
	return (1);
}
