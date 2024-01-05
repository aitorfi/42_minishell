/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:05:39 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 11:26:54 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Envía el carácter ’c’ al file descriptor especificado.*/

#include "libft.h"
/*
#include <unistd.h>

void    ft_putchar_fd(char c, int fd);

int	main(void)
{
	char	c;
	int		fd;

	c = 'c';
	fd = 2;
	ft_putchar_fd(c, fd);
	return (0);	
}
*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
