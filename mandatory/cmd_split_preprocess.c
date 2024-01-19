/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split_preprocess.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:11:47 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/19 18:23:49 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	count_end_word(char const *s, char c, t_preprocess *d)
{
	while (s[d->final] != c && s[d->final] != 0)
	{
		if (s[d->final] == '\"' || s[d->final] == '\'')
		{
			d->flag = 1;
			d->quote = s[d->final++];
			while (s[d->final] && s[d->final] != d->quote)
				d->final++;
			if (s[d->final])
			{
				d->flag = 0;
				d->final++;
			}
		}
		else
			d->final++;
	}
	return (d->final);
}

static size_t	count_start_word(char const *s, char c, t_preprocess *d)
{
	while (s[d->init] == c && s[d->init] != 0)
		d->init++;
	if (s[d->init] != c && s[d->init] != 0 && d->flag == 0)
	{
		d->count++;
		d->start = d->init;
	}
	if (s[d->init] == '\"' || s[d->init] == '\'')
	{
		d->flag = 1;
		d->quote = s[d->init++];
		while (s[d->init] && s[d->init] != d->quote)
			d->init++;
		if (s[d->init])
		{
			d->flag = 0;
			d->init++;
		}
	}
	return (d->start);
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
	if (d.flag)
		print_error_quote(d.quote);
	return (d.count);
}

char	**ft_split_preprocess(char const *s, char c)
{
	char			**split;
	t_preprocess	d_split;

	d_init(&d_split);
	split = (char **)malloc((count_word_preprocess(s, c) + 1) * sizeof(char *));
	if (split == 0)
		return (0);
	d_split.limit = -1;
	d_split.final = 0;
	while (++d_split.limit < count_word_preprocess(s, c))
	{
		d_split.init = d_split.final;
		d_split.start = count_start_word(s, c, &d_split);
		d_split.final = d_split.init;
		d_split.end = count_end_word(s, c, &d_split);
		split[d_split.limit] = malloc (sizeof(char)
				* (d_split.end - d_split.start + 1));
		if (split[d_split.limit] == 0)
			return (ft_free_split_preprocess(split, d_split.limit));
		ft_strlcpy(split[d_split.limit], (char *)(s + d_split.start),
			d_split.end - d_split.start + 1);
	}
	split[d_split.limit] = 0;
	return (split);
}
/*
int	main(void)
{
	char	*line;
	size_t	count;
	char	**arguments;
	size_t	i;

	line = "ls -l | grep \'hola que tal\' aqui 
	\'estoy 1adios \"   pepe \"   adios\' 2\'ho\'la \"que tal\"";
	count = count_word_preprocess(line, ' ');
	arguments = ft_split_preprocess(line, ' ');
	printf("%zu\n", count);
	i = 0;
	while (arguments[i])
	{
		printf("argument: %s\n", arguments[i]);
		i++;
	}
	return (0);
}*/
