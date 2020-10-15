/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 00:00:00 by dfinnis           #+#    #+#             */
/*   Updated: 2020/10/01 00:00:00 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

static char	*ft_strjoin_bin(char const *s1, char const *s2)
{
	char			*fresh;
	unsigned long	i;

	if (!s1 || !s2)
		return (0);
	if (!(fresh = ft_strnew(g_bitlen + 1)))
		return (NULL);
	i = 0;
	while (i < g_bitlen)
	{
		fresh[i] = s1[i];
		i++;
	}
	fresh[g_bitlen] = s2[0];
	fresh[g_bitlen + 1] = '\0';
	return (fresh);
}

static int	cp_char(char **line, char *str)
{
	char	*tmp;

	tmp = NULL;
	tmp = *line;
	if (!(*line = ft_strjoin_bin(*line, str)))
	{
		ft_freestr(str);
		return (-1);
	}
	ft_freestr(tmp);
	ft_freestr(str);
	return (0);
}

int			read_fd(const int fd, char **line)
{
	char	*str;
	int		k;

	if (line == NULL || fd < 0 || !(*line = ft_strdup("")))
		return (-1);
	g_bitlen = 0;
	k = 1;
	while (k > 0)
	{
		if (!(str = ft_strnew(1)))
			return (-1);
		if ((k = read(fd, str, 1)) == -1)
			exit(1);
		if ((cp_char(line, str)) == -1)
			return (-1);
		if (k == 0 && !*line[0])
			return (0);
		else if (k == 0 && *line[0])
			return (1);
		g_bitlen++;
	}
	return (-1);
}
