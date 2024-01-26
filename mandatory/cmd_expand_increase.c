/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand_increase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:11:42 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/26 15:51:57 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*copy_ret(char **ret, char *join)
{
	size_t	i;
	size_t	j;
	size_t	c;

	i = 0;
	c = 0;
	while (ret[i])
	{
		j = 0;
		while (ret[i][j])
		{
			join[c] = ret[i][j];
			j++;
			c++;
		}
		if (ret[i][j] == 0)
		{
			join[c] = ' ';
			c++;
		}
		i++;
	}
	return (join);
}

char	*increase_ret(char **ret)
{
	size_t	j;
	size_t	i;
	size_t	amount;
	char	*join;

	i = 0;
	j = 0;
	amount = 0;
	while (ret[i])
	{
		j = 0;
		while (ret[i][j])
		{
			j++;
			amount++;
		}
		i++;
		amount++;
	}
	join = ft_calloc(amount + 1, 1);
	if (join == NULL)
		return (perror("malloc error while expanding $"), NULL);
	join = copy_ret(ret, join);
	return (join);
}

char	**increase_routine(char **ret)
{
	char	**temp;
	char	*join;

	temp = ret;
	join = increase_ret(ret);
	if (join == NULL)
		return (perror("malloc error while expanding $"), NULL);
	ft_free_env(temp);
	ret = ft_split_preprocess(join, ' ');
	if (ret == NULL)
		return (perror("malloc error while expanding $"), NULL);
	free(join);
	return (ret);
}

void	find_dollar(t_expand *d)
{
	while (d->keep[d->i] && d->keep[d->i] != '$')
	{
		if (d->keep[d->i] == '\'')
		{
			d->i++;
			while (d->keep[d->i] && d->keep[d->i] != '\'')
				d->i++;
		}
		d->i++;
	}
}
