/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:28:57 by afidalgo          #+#    #+#             */
/*   Updated: 2024/01/12 19:13:47 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*join_lines(char *line1, char *line2);
static char	*get_heredoc_path(void);

char	*create_heredoc(char *limit)
{
	int		heredoc_end_found;
	char	*line;
	char	*hist_line;
	char	*path;

	hist_line = ft_strdup("");
	if (hist_line == NULL)
		return (NULL);
	path = get_heredoc_path();
	if (path == NULL)
		return (free_massive(hist_line));
	heredoc_end_found = 0;
	while (!heredoc_end_found)
	{
		line = readline("heredoc> ");
		if (line == NULL)
			return (free_massive(hist_line));
		if (ft_strncmp(line, limit, ft_strlen(line)) == 0)
			heredoc_end_found = 1;
		if (heredoc_end_found)
			create_file(path, hist_line);
		hist_line = join_lines(hist_line, line);
		if (hist_line == NULL)
			return (free_massive(path));
	}
	add_history(hist_line);
	return (path);
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
