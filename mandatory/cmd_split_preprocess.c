/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split_preprocess.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:11:47 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/18 18:57:09 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	count_end_word(char const *s, char c, t_preprocess *d)
{
	while (s[d->final] != c && s[d->final] != 0)
	{
		if (s[d->final] == '\"' || s[d->final] == '\'')
		{
			if (s[d->final] == '\"')
				d->flag_double = 0;
			else if (s[d->final] == '\'')
				d->flag_single = 0;
		}
		d->final++;
	}
}

static void	count_start_word(char const *s, char c, t_preprocess *d)
{
	while (s[d->init] == c && s[d->init] != 0)
		d->init++;
	if (s[d->init] != c && s[d->init] != 0 && d->flag_double == 0 && d->flag_single == 0)
		d->count++;
	if (s[d->init] == '\"' || s[d->init] == '\'')
	{
		if (s[d->init] == '\"')
		{
			if (d->flag_double)
				d->flag_double = 0;
			else
				d->flag_double = 1;
		}
		else if (s[d->init] == '\'')
		{
			if (d->flag_single)
				d->flag_single = 0;
			else
				d->flag_single = 1;
		}
		d->init++;
	}
}

static void		d_init(t_preprocess *d)
{
	d->final = 0;
	d->count = 0;
	d->init = 0;
	d->flag_single = 0;
	d->flag_double = 0;
}

static size_t	count_word_preprocess(char const *s, char c)
{
	t_preprocess	d;

	d_init(&d);
	while (s[d.init] != 0)
	{
		d.init = d.final;
		count_start_word(s, c, &d);
		d.final = d.init;
		count_end_word(s, c, &d);
		d.init = d.final;
	}
	return (d.count);
}

int	main(void)
{
	char	*line;
	size_t	count;

	line = "ls -l | grep hola que tal aqui \'\"estoy adios   pepe\' \" \"  adios\" \'hola que tal\'";
	count = count_word_preprocess(line, ' ');
	printf("%zu\n", count);
	return (0);
}
/*
static char	**ft_free(char **split, size_t limit)
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

char	**ft_split_preprocess(char const *s, char c)
{
	char	**split;
	size_t	limit;
	size_t	init;
	size_t	final;

	split = (char **)malloc((ft_count_word_preprocess(s, c) + 1) * sizeof(char *));
	if (split == 0)
		return (0);
	limit = -1;
	final = 0;
	while (++limit < ft_count_word(s, c))
	{
		init = final;
		while (s[init] == c && s[init] != 0)
			init++;
		final = init;
		while (s[final] != c && s[final] != 0)
			final++;
		split[limit] = malloc (sizeof(char) * (final - init + 1));
		if (split[limit] == 0)
			return (ft_free(split, limit));
		ft_strlcpy(split[limit], (char *)(s + init), final - init + 1);
	}
	split[limit] = 0;
	return (split);
}*/
