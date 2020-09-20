#include "../inc/ft_ssl.h"

static int	cp_char(char **line, char *str)
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

int			read_fd(const int fd, char **line)
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
		if ((g = read_fd_error(line, str)) == -1)
			return (-1);
		if (k == 0 && !*line[0])
			return (0);
		else if (k == 0 && *line[0])
			return (1);
	}
	return (-1);
}

void	read_file(char *filepath, t_args *args)
{
	char *input;
	int	error;
	int	fd;

	input = NULL;
	if ((fd = open(filepath, O_RDONLY)) == -1)
	{
		ft_printf("%s: %s: %s\n", g_cmd, filepath, strerror(errno));
		return;
	}
	// if directory?? deal with!!!
	if ((error = read_fd(fd, &input) == -1))
		ft_printf("error reading file\n", error);// EXIT!!!!!!!!!
	// print_usage();??
	print_prefix(filepath, args);
	hash(input);
	print_suffix(filepath, args);
	// ft_printf("\n");
}

char	*read_stdin(void)
{
	char *input;
	int	error;

	input = NULL;
	if ((error = read_fd(0, &input) == -1))
		ft_printf("error reading stdin\n", error);// EXIT!!!!!!!!!
	// ft_printf("input stdin: %s\n", input);//
	// hash(input);
	return input;
}
