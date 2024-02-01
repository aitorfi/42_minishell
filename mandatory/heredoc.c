/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:28:57 by afidalgo          #+#    #+#             */
/*   Updated: 2024/02/01 20:15:42 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*readline_loop(char *limit);
static char	*join_lines(char *line1, char *line2);

char	*create_heredoc(char *limit, t_mshell *mshell)
{
	char	*path;
	char	*content;

	content = readline_loop(limit);
	if (content == NULL)
		return (notify_error_ptr("Error al crear heredoc"));
	create_file(mshell->heredoc_path, content, 00644);
	free(content);
	path = ft_strdup(mshell->heredoc_path);
	if (path == NULL)
		return (notify_error_ptr("Error al crear heredoc"));
	return (path);
}

static char	*readline_loop(char *limit)
{
	char	*line;
	char	*content;

	content = ft_strdup("");
	if (content == NULL)
		return (NULL);
	line = readline("heredoc> ");
	if (line == NULL)
		return (free_massive(content, NULL));
	while (ft_strncmp(line, limit, ft_strlen(line)) != 0)
	{
		content = join_lines(content, line);
		if (content == NULL)
			return (NULL);
		line = readline("heredoc> ");
		if (line == NULL)
			return (free_massive(content, NULL));
	}
	free(line);
	return (content);
}

static char	*join_lines(char *line1, char *line2)
{
	char	*del_line;
	char	*ret_line;

	del_line = line2;
	line2 = ft_strjoin(line2, "\n");
	if (line2 == NULL)
		return (free_massive(del_line, line1, NULL));
	free(del_line);
	ret_line = ft_strjoin(line1, line2);
	if (ret_line == NULL)
		return (free_massive(line1, line2, NULL));
	free(line1);
	free(line2);
	return (ret_line);
}

char	*get_heredoc_path(char **envs)
{
	char	*home_dir;
	char	*path;
	int		i;

	i = 0;
	while (envs[i] && ft_strncmp(envs[i], "HOME=", 5))
		i++;
	if (envs[i] == NULL)
		home_dir = ft_strdup("./");
	else
		home_dir = ft_substr(envs[i], 5, ft_strlen(envs[i]) - 5);
	if (home_dir == NULL)
		return (NULL);
	if (home_dir[ft_strlen(home_dir) - 1] == '/')
		path = ft_strjoin(home_dir, ".msh_heredoc");
	else
		path = ft_strjoin(home_dir, "/.msh_heredoc");
	free(home_dir);
	return (path);
}
