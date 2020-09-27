#include "../inc/ft_ssl.h"

int			flag_s(int argc, char **argv, int i, t_args *args)
{
	if (i + 2 > argc)
		ft_printf("Error: no string here!!\n");// EXIT!!!
	i++;
	args->flag_s = 1;
	print_prefix(argv[i], args);
	g_cmd_func(argv[i]);
	print_suffix(argv[i], args);
	args->flag_s = 0;
	return (i);
}

void		flag_p(void)
{
	char *input;

	input = read_stdin();
	ft_printf(input);
	g_cmd_func(input);
	ft_printf("\n");
}

static int	read_arg(int argc, char **argv, t_args *args, int i)
{
	if (ft_strcmp((argv[i]), "-p") == 0)
		flag_p();
	else if (ft_strcmp((argv[i]), "-q") == 0 && args->first == 1)
	{
		args->flag_q = 1;
		args->first = 0;
	}
	else if (ft_strcmp((argv[i]), "-r") == 0 && args->first == 1)
	{
		args->flag_r = 1;
		args->first = 0;
	}
	else if (ft_strcmp((argv[i]), "-s") == 0 && args->first == 1)
		i = flag_s(argc, argv, i, args);
	else
	{
		read_file(argv[i], args);
		args->first = 0;
	}
	return (++i);
}

static void	read_command(char *command, t_args *args)
{
	args->command = command;
	(ft_strcmp(command, "md5") == 0) ? g_cmd_func = &md5 : 0;
	(ft_strcmp(command, "sha256") == 0) ? g_cmd_func = &sha256 : 0;
	if (g_cmd_func == NULL)
		print_usage();// correct action here?
}

static void	init_ssl(t_args *args)
{
	ft_bzero(args, sizeof(*args));
	args->first = 1;
}

int			main(int argc, char **argv)
{
	int 	i;
	t_args	args;

	i = 2;
	init_ssl(&args);
	if (argc == 1)
		print_usage();
	else
	{
		read_command(argv[1], &args);
		if (argc == 2)
			g_cmd_func(read_stdin());
		else
			while (i < argc)
				i = read_arg(argc, argv, &args, i);
	}
	return (0);
}

// flag: -s "string1" -s "string2"
// file as direct argument: ./ft_ssl md5 file
// standard in: -p OR echo "string" | ./ft_ssl md5
