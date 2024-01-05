/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:20:31 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 11:25:43 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Envía la string ’s’ al file descriptor dado, seguido de un salto de línea*/

#include "libft.h"
/*
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd);

int	main(void)
{
	char	s[] = "Hola Mundo";
	int		fd;

	fd = 1;
	ft_putendl_fd(s, fd);
	return (0);
}
*/
void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = -1;
	while (s[++i] != 0)
		write(fd, &s[i], 1);
	write(fd, "\n", 1);
}
