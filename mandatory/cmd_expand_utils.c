/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:36:22 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/26 10:02:38 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_dollar_question(void)
{
	char	*dollar_question;

	dollar_question = ft_itoa(g_result);
	return (dollar_question);
}

char	*search_expand(char *to_expand, t_mshell *mini_data)
{
	char	*temp;

	if (!ft_strncmp(to_expand, "?", ft_strlen(to_expand)))
		return (get_dollar_question());
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
