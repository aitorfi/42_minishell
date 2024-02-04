/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 12:58:14 by aitorfi           #+#    #+#             */
/*   Updated: 2024/02/01 20:15:41 by afidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*create_file(char *path, char *content, mode_t mode)
{
	int	fd;

	fd = open(path, O_RDWR | O_TRUNC | O_CREAT, mode);
	if (fd == -1)
		return (notify_error_ptr("Error al escribir en el fichero"));
	if (write(fd, content, ft_strlen(content)) == -1)
	{
		close(fd);
		return (notify_error_ptr("Error al escribir en el fichero"));
	}
	close(fd);
	return (path);
}

char	*get_file_content(char *path)
{
	int		fd;
	char	*content;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (notify_error_ptr("Error al obtener el contenido del fichero"));
	content = get_file_content_fd(fd);
	close(fd);
	if (content == NULL)
		return (notify_error_ptr("Error al obtener el contenido del fichero"));
	return (content);
}

char	*get_file_content_fd(int fd)
{
	char	*content;
	char	*del;
	char	*line;

	line = get_next_line(fd);
	if (line == NULL)
		return (NULL);
	content = ft_strdup("");
	if (content == NULL)
		return (free_massive(line, NULL));
	while (ft_strchr(line, '\n'))
	{
		del = content;
		content = ft_strjoin(content, line);
		if (content == NULL)
			return (free_massive(del, line, NULL));
		free(del);
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			return (free_massive(content, NULL));
	}
	return (content);
}

int	close_massive(int fd, ...)
{
	va_list	args;

	va_start(args, fd);
	close(fd);
	fd = va_arg(args, int);
	while (fd)
	{
		close(fd);
		fd = va_arg(args, int);
	}
	va_end(args);
	return (EXIT_FAILURE);
}
