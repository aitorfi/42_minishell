/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitorfi <aitorfi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:58:14 by aitorfi           #+#    #+#             */
/*   Updated: 2024/01/13 14:07:13 by aitorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*create_file(char *path, char *content)
{
	int	fd;

	fd = open(path, O_RDWR | O_TRUNC | O_CREAT, 0000644);
	if (fd == -1)
		return (notify_error_ptr("Error"));
	if (write(fd, content, ft_strlen(content)) == -1)
	{
		close(fd);
		return (notify_error_ptr("Error"));
	}
	close(fd);
	return (path);
}

char	*get_file_content(int fd)
{
	char	*content;
	char	*del;
	char	*line;

	line = get_next_line(fd);
	if (line == NULL)
		return (NULL);
	content = ft_strdup("");
	if (content == NULL)
		return (free_massive(line));
	while (ft_strchr(line, '\n'))
	{
		del = content;
		content = ft_strjoin(content, line);
		if (content == NULL)
			return (free_massive(del, line));
		free(del);
		free(line);
		line = get_next_line(fd);
		printf("line = %s\n", line);
		if (line == NULL)
			return (free_massive(content));
	}
	return (content);
}
