#include "../inc/ft_ssl.h"

char	*ft_strcpy2(char *dst, const char *src)
{
	unsigned long	i;

	i = 0;
	while (i < g_len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strcat2(char *s1, const char *s2)
{
	s1[g_len] = s2[0];
	s1[g_len + 1] = '\0';
	return (s1);
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	char	*fresh;

	if (!s1 || !s2)
		return (0);
	if (!(fresh = ft_strnew(g_len + 1)))
		return (NULL);
	ft_strcpy2(fresh, s1);
	ft_strcat2(fresh, s2);
	return (fresh);
}

static int	cp_char(char **line, char *str)
{
	char	*tmp;

	tmp = NULL;
	tmp = *line;
	if (!(*line = ft_strjoin2(*line, str)))
		return (-1);
	ft_freestr(tmp);
	ft_freestr(str);
	return (0);
}

static int	read_fd_error(char **line, char *str)
{
	int	g;

	if ((g = cp_char(line, str)) == -1)
	{
		ft_freestr(str);
		return (-1);
	}
	return (0);
}

static int	read_fd(const int fd, char **line)
{
	char	*str;
	int		k;

	if (line == NULL || fd < 0 || !(*line = ft_strdup("")))
		return (-1);
	k = 1;
	while (k > 0)
	{
		if (!(str = ft_strnew(1)))
			return (-1);
		if ((k = read(fd, str, 1)) == -1)
			exit(1);
		if ((read_fd_error(line, str)) == -1)
			return (-1);
		if (k == 0 && !*line[0])
			return (0);
		else if (k == 0 && *line[0])
			return (1);
		g_len++;
	}
	return (-1);
}

static int	is_regular_file(const char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

void		read_file(char *filepath, t_args *args)
{
	char	*input;
	int		error;
	int		fd;

	input = NULL;
	if ((fd = open(filepath, O_RDONLY)) == -1)
	{
		ft_dprintf(2, "%s: %s: %s\n", args->command, filepath, strerror(errno));
		return ;
	}
	if (!is_regular_file(filepath))
	{
		ft_dprintf(2, "%s: %s: Is a directory\n", args->command, filepath);
		return ;
	}
	if ((error = read_fd(fd, &input) == -1))
	{
		ft_dprintf(2, "%s: %s: Error reading file\n", args->command, filepath);
		return ;
	}
	g_len *= 8;
	print_prefix(filepath, args);
	g_cmd_func(input);
	print_suffix(filepath, args);
}

char		*read_stdin(void)
{
	char	*input;
	int		error;

	input = NULL;
	if ((error = read_fd(0, &input) == -1))
		ft_dprintf(2, "error reading stdin\n", error);// EXIT!!!!!!!!!
	return (input);
}
