/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:46:06 by alvicina          #+#    #+#             */
/*   Updated: 2023/11/24 11:27:18 by alvicina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_gnl(char **s1)
{
	free (*s1);
	*s1 = NULL;
	return (0);
}

char	*ft_substr_gnl(char *str, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!str)
		return (0);
	if (start > ft_strlen(str))
	{
		res = malloc(sizeof(char) * (1));
		if (!res)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	if (ft_strlen(str) - start < len)
		len = ft_strlen(str) - start;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (start < ft_strlen(str) && i < len && str[start])
		res[i++] = str[start++];
	res[i] = '\0';
	return (res);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	char	x;
	int		i;

	x = (char)c;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != x && s[i] != 0)
		i++;
	if (s[i] == x)
		return ((char *)(s + i));
	else
		return ((char *)(0));
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	c;

	if (!s1 || !s2)
		return (0);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (free(s1), (char *) 0);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	c = -1;
	while (s2[++c])
		str[i + c] = s2[c];
	str[i + c] = '\0';
	free(s1);
	return (str);
}
