/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 00:00:00 by dfinnis           #+#    #+#             */
/*   Updated: 2020/10/01 00:00:00 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

static int	is_regular_file(const char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

static int	is_directory(const char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

void		read_file(char *filepath, t_args *args)
{
	char	*input;
	int		fd;

	input = NULL;
	if ((fd = open(filepath, O_RDONLY)) == -1)
	{
		ft_dprintf(2, "%s: %s: %s\n", args->command, filepath, strerror(errno));
		return ;
	}
	if (!is_regular_file(filepath))
	{
		if (is_directory(filepath))
			ft_dprintf(2, "%s: %s: Is a directory\n", args->command, filepath);
		else
			ft_dprintf(2, "%s: %s: Is not a file\n", args->command, filepath);
		return ;
	}
	if (read_fd(fd, &input) == -1)
	{
		ft_dprintf(2, "%s: %s: Error reading file\n", args->command, filepath);
		return ;
	}
	print_prefix(filepath, args);
	g_cmd_func(input);
	print_suffix(filepath, args);
	ft_freestr(input);
}

void		read_stdin(int flag_p)
{
	char	*input;

	input = NULL;
	if (read_fd(0, &input) == -1)
		error_exit("reading stdin failed");
	if (flag_p)
		ft_printf(input);
	g_cmd_func(input);
	ft_printf("\n");
	ft_freestr(input);
}

void		read_stdin_command(t_args *args)
{
	char	*input;
	int		error;

	input = NULL;
	ft_putstr("FT_SSL> ");
	if ((error = get_next_line(0, &input) == -1))
		error_exit("reading stdin failed");
	if (ft_strcmp(input, "quit") == 0)
	{
		ft_freestr(input);
		exit(0);
	}
	if (ft_strcmp(input, "") == 0)
	{
		ft_freestr(input);
		read_stdin_command(args);
	}
	read_command(input, args);
	ft_freestr(input);
	if (g_cmd_func == NULL)
		read_stdin_command(args);
	else
		read_stdin(0);
}
