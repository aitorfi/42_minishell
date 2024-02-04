/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split_preprocess.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:11:47 by alvicina          #+#    #+#             */
/*   Updated: 2024/02/02 11:39:31 by alejandro        ###   ########.fr       */
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

static size_t	count_pre(char const *s, char c, size_t *s_quote)
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
	{
		print_error_quote(d.quote);
		*s_quote = 1;
	}
	return (d.count);
}

char	**ft_split_preprocess(char const *s, char c)
{
	t_preprocess	d_split;

	d_init(&d_split);
	d_split.s = malloc((count_pre(s, c, &d_split.flag) + 1) * sizeof(char *));
	if (d_split.s == NULL)
		return (perror("error in malloc split preprocess"), NULL);
	if (d_split.flag == 1)
		return (free(d_split.s), (char **) 1);
	d_split.limit = -1;
	d_split.final = 0;
	while (++d_split.limit < count_pre(s, c, &d_split.flag))
	{
		d_split.init = d_split.final;
		d_split.start = count_start_word(s, c, &d_split);
		d_split.final = d_split.init;
		d_split.end = count_end_word(s, c, &d_split);
		d_split.s[d_split.limit] = malloc (sizeof(char)
				* (d_split.end - d_split.start + 1));
		if (d_split.s[d_split.limit] == 0)
			return (ft_free_split_preprocess(d_split.s, d_split.limit));
		ft_strlcpy(d_split.s[d_split.limit], (char *)(s + d_split.start),
			d_split.end - d_split.start + 1);
	}
	d_split.s[d_split.limit] = 0;
	return (d_split.s);
}
/*
int	main(void)
{
	char	*line;
	size_t	count;
	char	**arguments;
	size_t	i;

	line = "ls -l | grep \'hola que tal\' aqui \'estoy 1adios \"   pepe \"   
	adios\' 2\'ho\'la \"que tal\"";
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
