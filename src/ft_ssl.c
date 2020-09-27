#include "../inc/ft_ssl.h"

void	print_usage(void)
{
	ft_putstr("\nusage:\t./ft_ssl []");
	// free(eveything);
	exit(1);
}

void	print_prefix(char *input, t_args *args)
{
	unsigned long i;
	unsigned long len;

	if (!args->flag_q && !args->flag_r)
	{
		i = 0;
		len = ft_strlen(g_cmd_str);
		while (i < len)
			ft_printf("%c", ft_toupper(g_cmd_str[i++]));
		if (args->flag_s)
			ft_printf(" (\"%s\") = ", input);
		else
			ft_printf(" (%s) = ", input);
	}
}

void	print_suffix(char *input, t_args *args)
{
	if (args->flag_r)
	{
		if (args->flag_s)
			ft_printf(" \"%s\"", input);
		else
			ft_printf(" %s", input);
	}
	ft_printf("\n");
}

int		flag_s(int argc, char **argv, int i, t_args *args)
{
	if (i + 2 > argc)
		ft_printf("Error: no string here!!\n");// EXIT!!!
	i++;
	args->flag_s = 1;
	print_prefix(argv[i], args);
	g_command(argv[i]);
	print_suffix(argv[i], args);
	args->flag_s = 0;
	return i;
}

static int	read_arg(int argc, char **argv, t_args *args, int i, unsigned int *first)
{
	char *input;

	input = NULL;
	if (ft_strcmp((argv[i]), "-p") == 0)
	{
		args->flag_p = 1;//
		input = read_stdin();
		ft_printf(input);
		g_command(input);
	}
	else if (ft_strcmp((argv[i]), "-q") == 0 && (*first) == 0)
	{
		args->flag_q = 1;
		(*first)++;
	}
	else if (ft_strcmp((argv[i]), "-r") == 0 && (*first) == 0)
	{
		args->flag_r = 1;
		(*first)++;
	}
	else if (ft_strcmp((argv[i]), "-s") == 0 && (*first) == 0)
		i = flag_s(argc, argv, i, args);
	else
	{
		// ft_printf("arg: %s\n", argv[i]);//
		read_file(argv[i], args);
		(*first)++;
	}
	return (++i);
}

void	read_command(char *command)
{
	g_cmd_str = command;
	(ft_strcmp(command, "md5") == 0) ? g_command = &md5 : 0 ;
	(ft_strcmp(command, "sha256") == 0) ? g_command = &sha256 : 0 ;
	if (g_command == NULL)
		print_usage();// correct action here?
}

void	read_args(int argc, char **argv, t_args *args)
{
	int i;
	unsigned int	first;

	i = 2;
	first = 0;
	if (argc == 1)
		print_usage();
	else
	{
		read_command(argv[1]);
		if (argc == 2)
			g_command(read_stdin());
		else
		{
			while (i < argc)
				i = read_arg(argc, argv, args, i, &first);
		}
	}
}

static void	init_ssl(t_args *args)
{
	ft_bzero(args, sizeof(*args));
}

int		main(int argc, char **argv)
{
	t_args	args;

	init_ssl(&args);
	read_args(argc, argv, &args);
	// ft_printf("\n\nargs.flag_p: %d\n", args.flag_p);//rm!!!
	// ft_printf("args.flag_q: %d\n", args.flag_q);//rm!!!
	// ft_printf("args.flag_r: %d\n", args.flag_r);//rm!!!
	// ft_printf("args.flag_s: %d\n", args.flag_s);//rm!!!
	return (0);
}

// flag: -s "string1" -s "string2"
// file as direct argument: ./ft_ssl md5 file
// standard in: -p OR echo "string" | ./ft_ssl md5