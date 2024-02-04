/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_preprocessor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejandro <alejandro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:26:09 by afidalgo          #+#    #+#             */
/*   Updated: 2024/02/02 11:40:20 by alejandro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	loop_trim(t_trim *d, char **ret)
{
	d->j = 0;
	d->c = 0;
	while (ret[d->i][d->j] && ret[d->i][d->j + 1])
	{
		if (ret[d->i][d->j] == '\"' || ret[d->i][d->j] == '\'')
		{
			d->char_q = ret[d->i][d->j];
			if (ret[d->i][d->j + 1] != d->char_q)
				d->temp[d->c++] = ret[d->i][d->j++ + 1];
			d->j++;
			while (ret[d->i][d->j] && ret[d->i][d->j] != d->char_q)
				d->temp[d->c++] = ret[d->i][d->j++];
			if (ret[d->i][d->j] == d->char_q)
			{
				d->char_q = 0;
				d->j++;
			}
		}
		else
			d->temp[d->c++] = ret[d->i][d->j++];
	}
}

static void	d_init_trim(t_trim *d)
{
	d->i = -1;
	d->j = 0;
	d->c = 0;
	d->char_q = 0;
	d->temp = NULL;
}

static char	**exec_trim(char **ret)
{
	t_trim	d;

	d_init_trim(&d);
	while (ret[++d.i])
	{
		d.temp = malloc(sizeof(char) * ft_strlen(ret[d.i]) + 1);
		if (d.temp == NULL)
			return (perror("malloc error  while trim"), NULL);
		loop_trim(&d, ret);
		d.temp[d.c] = 0;
		if (ret[d.i][d.j] != '\'' && ret[d.i][d.j] != '\"')
		{
			d.temp[d.c++] = ret[d.i][d.j];
			d.temp[d.c] = 0;
		}
		free(ret[d.i]);
		ret[d.i] = d.temp;
	}
	return (ret);
}

static char	*replace_chars(char *str, char *to_find, char replace)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (to_find[j])
		{
			if (str[i] == to_find[j])
				str[i] = replace;
			j++;
		}
		i++;
	}
	return (str);
}

char	**preprocess(char *line, t_mshell *mini_data)
{
	char		**ret;

	ret = NULL;
	line = replace_chars(line, "\t\n\v\f\r", ' ');
	ret = ft_split_preprocess(line, ' ');
	if (ret == NULL)
		return (NULL);
	if (ret == (char **) 1)
		return ((char **) 1);
	ret = do_expand(ret, mini_data);
	if (ret == NULL)
		return (perror("malloc error while expanding $"), NULL);
	ret = exec_trim(ret);
	if (ret == NULL)
		return (perror("malloc error while trim $"), NULL);
	return (ret);
}
/*
int	main(int argc, char **argv, char **envp)
{
	//char	line[100] = "hola \t\v\f\r que\t\n\v\f\rtal ";
	char		*line;
	char		**line_ast;
	size_t		i;
	t_mshell	mini_data;
	char		*arguments[4];

	arguments[0] = "export";
	arguments[1] = "ALE=1hola 2que 3tal";
	arguments[2] = NULL;
	arguments[3] = NULL;
	(void) argc;
	(void) argv;
	i = 0;
	mini_data.env_custom = do_env_init(envp, 0);
	do_export(&mini_data, arguments);
	//while (mini_data.env_custom[i])
	//{
	//	printf("%s\n", mini_data.env_custom[i]);
	//	i++;
	//}
	line = readline("minishell> ");
	line_ast = preprocess(line, &mini_data);
	if (line_ast == NULL)
	{
		ft_free_env(mini_data.env_custom);
		free(line);
		return (-1);
	}
	i = 0;
	while (line_ast[i])
	{
		printf("hola\n");
		printf("%s\n", line_ast[i]);
		i++;
	}
	ft_free_env(line_ast);
	ft_free_env(mini_data.env_custom);
	free(line);
	//system("leaks a.out");
	return (0);
}
*/