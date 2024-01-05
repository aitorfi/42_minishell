/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:33:50 by alvicina          #+#    #+#             */
/*   Updated: 2023/09/29 11:24:13 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Envía el número ’n’ al file descriptor dado. He utilizado recursividad*/

#include "libft.h"
/*
#include <unistd.h>
#include <stdlib.h>

void	ft_putnbr_fd(int n, int fd);

int	main(void)
{
	int	n;
	int	fd;

	n = 500;
	fd = 1;
	ft_putnbr_fd(n, fd);
	return (0);
}
*/

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (n < 0)
		{
			n = n * (-1);
			write(fd, "-", 1);
		}
		if (n > 9)
			ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
}
