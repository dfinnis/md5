#include "../inc/ft_ssl.h"

static int	ft_get_line(char **line, char *str)
{
	char	*tmp;

	tmp = NULL;
	tmp = *line;
	if (!(*line = ft_strjoin(*line, str)))
		return (-1);
	ft_freestr(tmp);
	ft_freestr(str);
	return (0);
}

static int	ft_gnl_error(char **line, char *str)
{
	int	g;

	g = 0;
	if ((g = ft_get_line(line, str)) == 1)
		return (1);
	else if (g == -1)
	{
		ft_freestr(str);
		return (-1);
	}
	return (0);
}

int			get_next_line2(const int fd, char **line)
{
	char	*str;
	int		k;
	int		g;

	if (line == NULL || fd < 0 || !(*line = ft_strdup("")))
		return (-1);
	k = 1;
	while (k > 0)
	{
		if (!(str = ft_strnew(1)))
			return (-1);
		if ((k = read(fd, str, 1)) == -1)
			exit(1);
		if ((g = ft_gnl_error(line, str)) == 1)
			return (1);
		else if (g == -1)
			return (-1);
		if (k == 0 && !*line[0])
			return (0);
		else if (k == 0 && *line[0])
			return (1);
	}
	return (-1);
}
