/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split_preprocess_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:27:32 by alvicina          #+#    #+#             */
/*   Updated: 2024/02/01 10:59:35 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	d_init(t_preprocess *d)
{
	d->final = 0;
	d->count = 0;
	d->init = 0;
	d->flag = 0;
	d->limit = 0;
	d->quote = 0;
	d->start = 0;
	d->end = 0;
	d->s = NULL;
}

char	**ft_free_split_preprocess(char **split, size_t limit)
{
	limit = 0;
	while (split[limit] != 0)
	{
		free(split[limit]);
		limit++;
	}
	free(split);
	return (0);
}

void	print_error_quote(int c)
{
	g_result = 1;
	if (c == '\"')
		ft_putstr_fd("minishell> EOF while looking for matching \"\n", 2);
	else
		ft_putstr_fd("minishell> EOF while looking for matching \'\n", 2);
}
