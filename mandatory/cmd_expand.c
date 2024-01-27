/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:46:05 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/26 16:56:15 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_new_string_expanded(t_expand *d)
{
	d->temp = d->keep;
	d->keep = ft_strjoin(d->first, d->search);
	if (d->keep == NULL)
		return (perror("malloc error while expanding $"), NULL);
	d->j = 0;
	while (d->keep[d->j])
		d->j++;
	if (d->flag)
		free(d->temp);
	free(d->first);
	free(d->search);
	d->flag = 1;
	d->first = d->keep;
	d->keep = ft_strjoin(d->keep, d->second);
	if (d->keep == NULL)
		return (perror("malloc error while expanding $"), NULL);
	free(d->first);
	free(d->second);
	return (d->keep);
}

static int	get_substrings_expand(t_expand *d, size_t pos, char **ast)
{
	if (d->keep == NULL)
		d->keep = ast[pos];
	d->i = d->j;
	find_dollar(d);
	if (!d->keep[d->i])
		return (1);
	d->first = ft_substr(d->keep, 0, d->i);
	if (d->first == NULL)
		return (perror("malloc error while expanding $"), 2);
	d->j = ++d->i;
	while (d->keep[d->j] && (ft_isalnum(d->keep[d->j]) || d->keep[d->j] == '_'))
		d->j++;
	if (d->j == d->i && d->keep[d->j] == '?')
		d->j++;
	d->second = ft_substr(d->keep, d->j, ft_strlen(d->keep) - d->j);
	if (d->second == NULL)
		return (perror("malloc error while expanding $"), 2);
	d->to_expand = ft_substr(d->keep, d->i, d->j - d->i);
	if (d->to_expand == NULL)
		return (perror("malloc error while expanding $"), 2);
	return (0);
}

static char	*exec_expand_comp(char **ast, t_mshell *mini_data, size_t pos)
{
	t_expand	d;

	d_expand_init(&d);
	while (1)
	{
		d.result = get_substrings_expand(&d, pos, ast);
		if (d.result == 2)
			return (NULL);
		else if (d.result == 1)
			break ;
		d.search = search_expand(d.to_expand, mini_data);
		free(d.to_expand);
		if (d.search == NULL)
			return (NULL);
		if (!get_new_string_expanded(&d))
			return (NULL);
	}
	return (d.keep);
}

static char	**exec_expand(char **ast,
t_mshell *mini_data, size_t pos)
{
	char	*new;

	new = exec_expand_comp(ast, mini_data, pos);
	if (new == NULL)
		return (NULL);
	if (ft_strncmp(new, ast[pos], ft_strlen(ast[pos])))
	{
		free(ast[pos]);
		ast[pos] = new;
	}
	return (ast);
}

char	**do_expand(char **ret, t_mshell *mini_data)
{
	size_t	i;

	i = 0;
	while (ret[i])
	{
		if (check_expand(ret[i]))
		{
			if (check_dollar(ret[i]))
			{
				if (!exec_expand(ret, mini_data, i))
					return (NULL);
			}
		}
		i++;
	}
	ret = increase_routine(ret);
	if (ret == NULL)
		return (NULL);
	return (ret);
}
