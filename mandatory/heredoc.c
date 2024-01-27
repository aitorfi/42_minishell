/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:28:57 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/27 13:05:04 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*readline_loop(char *limit);
static char	*join_lines(char *line1, char *line2);
static char	*get_heredoc_path(void);

char	*create_heredoc(char *limit)
{
	char	*path;
	char	*content;

	path = get_heredoc_path();
	if (path == NULL)
		return (notify_error_ptr("Error al crear heredoc"));
	content = readline_loop(limit);
	if (content == NULL)
		return (notify_error_ptr("Error al crear heredoc"));
	create_file(path, content);
	free(content);
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
		return (free_massive(content));
	while (ft_strncmp(line, limit, ft_strlen(line)) != 0)
	{
		content = join_lines(content, line);
		if (content == NULL)
			return (NULL);
		line = readline("heredoc> ");
		if (line == NULL)
			return (free_massive(content));
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
		return (free_massive(del_line, line1));
	free(del_line);
	ret_line = ft_strjoin(line1, line2);
	if (ret_line == NULL)
		return (free_massive(line1, line2));
	free(line1);
	free(line2);
	return (ret_line);
}

static char	*get_heredoc_path(void)
{
	// TODO: Get a path for the heredoc in the users HOME directory
	return (ft_strdup("./heredoc"));
}
