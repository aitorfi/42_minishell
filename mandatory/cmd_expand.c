/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:46:05 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/24 11:29:55 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_new_string_expanded(t_expand *d)
{
	d->temp = d->keep;
	d->keep = ft_strjoin(d->first, d->search);
	if (d->keep == NULL)
		return (perror("malloc error while expanding $"), NULL);
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
	d->i = 0;
	while (d->keep[d->i] && d->keep[d->i] != '$')
		d->i++;
	if (!d->keep[d->i])
		return (1);
	d->first = ft_substr(d->keep, 0, d->i);
	if (d->first == NULL)
		return (perror("malloc error while expanding $"), 2);
	d->j = d->i;
	while (d->keep[d->j] && d->keep[d->j] != ' ' && d->keep[d->j] != '\"'
		&& d->keep[d->j] != '\'')
		d->j++;
	d->second = ft_substr(d->keep, d->j, ft_strlen(d->keep) - d->j);
	if (d->second == NULL)
		return (perror("malloc error while expanding $"), 2);
	d->to_expand = ft_substr(d->keep, d->i + 1, d->j - d->i - 1);
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
	free(ast[pos]);
	ast[pos] = new;
	return (ast);
}

int	do_expand(char **ret, t_mshell *mini_data)
{
	size_t	i;
	char	*where_dollar;

	i = 0;
	while (ret[i])
	{
		if (check_expand(ret[i]))
		{
			where_dollar = check_dollar(ret[i]);
			if (where_dollar)
			{
				if (!exec_expand(ret, mini_data, i))
					return (1);
			}
		}
		i++;
	}
	return (0);
}

/*ls -l | grep 'hola $que tal'  adios$HOMENO   $PATH 'estoy 1adios "   pepe "   adios' 2'ho'la "que $USER hola $USER   hola   $PWD  hola"*/
/*ls -l | grep 'hola $que tal' $PATH 'estoy 1adios "   pepe "   adios' 2'ho'la "que $USER $USER $PWD hola"*/