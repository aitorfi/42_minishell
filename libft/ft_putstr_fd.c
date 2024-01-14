/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:27:30 by alvicina          #+#    #+#             */
/*   Updated: 2024/01/14 12:12:49 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Envía la string ’s’ al file descriptor especificado.*/

#include "libft.h"
/*
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd);

int	main(void)
{
	char	s[] = "Hola Mundo";
	int		fd;

	fd = 1;
	ft_putstr_fd(s, fd);
	return (0);
}
*/

int	ft_check_equal(char *s)
{
	size_t	i;
	int		flag;

	i = 0;
	flag = 0;
	while (s[i])
	{
		if (s[i] == '=')
			flag++;
		i++;
	}
	if (flag == 0)
		return (0);
	else
		return (1);
}

void	ft_putstr_export_fd(char *s, int fd)
{
	int	i;

	if (!ft_check_equal(s))
		return (ft_putstr_fd(s, 1));
	i = 0;
	while (s[i] && s[i] != '=')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, &s[i], 1);
	i++;
	write(1, "\"", 1);
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(1, "\"", 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = -1;
	while (s[++i] != 0)
		write(fd, &s[i], 1);
}
