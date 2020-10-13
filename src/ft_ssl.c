#include "../inc/ft_ssl.h"

static void	init_ssl(t_args *args)
{
	ft_bzero(args, sizeof(*args));
	args->first = 1;
}

static void	read_command(char *cmd, t_args *args)
{
	unsigned long i;

	args->command = cmd;
	i = 0;
	while (i < (sizeof(g_cmd_func_map) / sizeof(g_cmd_func_map[0])))
	{
		if (!strcmp(g_cmd_func_map[i].cmd, cmd) && g_cmd_func_map[i].func)
		{
			g_cmd_func = g_cmd_func_map[i].func;
			break ;
		}
		i++;
	}
	if (g_cmd_func == NULL)
	{
		ft_dprintf(2, "ft_ssl: Error: \'%s\' is an invalid command.\n", cmd);
		print_usage();
	}
}

static void	flag_s(int argc, char **argv, int i, t_args *args)
{
	if (++i >= argc)
	{
		ft_printf("%s: option requires an argument -- s\n", args->command);
		ft_printf("usage: %s [-pqr] [-s string] [files ...]\n", args->command);
		exit(1);
	}
	args->flag_s = 1;
	g_len = ft_strlen(argv[i]) * 8;
	print_prefix(argv[i], args);
	g_cmd_func(argv[i]);
	print_suffix(argv[i], args);
}

static int	read_arg(int argc, char **argv, t_args *args, int i)
{
	args->flag_s = 0;
	if (ft_strcmp((argv[i]), "-p") == 0 && args->first)
		read_stdin(1);
	else if (ft_strcmp((argv[i]), "-q") == 0 && args->first)
		args->flag_q = 1;
	else if (ft_strcmp((argv[i]), "-r") == 0 && args->first)
		args->flag_r = 1;
	else if (ft_strcmp((argv[i]), "-s") == 0 && args->first)
		flag_s(argc, argv, i++, args);
	else
	{
		read_file(argv[i], args);
		args->first = 0;
	}
	return (++i);
}

static void	stdin_cmd(t_args *args)
{
	char	*input;
	int		error;

	ft_putstr("FT_SSL> ");
	input = NULL;
	if ((error = get_next_line(0, &input) == -1))
	{
		ft_dprintf(2, "error reading stdin\n", error);
		exit(1);
	}
	if (ft_strcmp(input, "quit") == 0)
		exit(0);
	if (ft_strcmp(input, "") == 0)
		stdin_cmd(args);
	read_command(input, args);
	if (g_cmd_func == NULL)
		stdin_cmd(args);
	else
		read_stdin(0);
}

int			main(int argc, char **argv)
{
	int		i;
	t_args	args;

	i = 2;
	init_ssl(&args);
	if (argc == 1)
		stdin_cmd(&args);
	else
	{
		read_command(argv[1], &args);
		if (g_cmd_func == NULL)
			exit(0);
		if (argc == 2)
			read_stdin(0);
		else
		{
			while (i < argc)
				i = read_arg(argc, argv, &args, i);
			if (args.first && (args.flag_q || args.flag_r) && !args.flag_s)
				read_stdin(0);
		}
	}
	return (0);
}
