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
		len = ft_strlen(g_cmd);
		while (i < len)
			ft_printf("%c", ft_toupper(g_cmd[i++]));
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
	hash(argv[i]);
	print_suffix(argv[i], args);
	args->flag_s = 0;
	return i;
}

static int	read_arg(int argc, char **argv, t_args *args, int i)
{
	char *input;

	input = NULL;
	if (ft_strcmp((argv[i]), "-p") == 0)
	{
		args->flag_p = 1;//
		input = read_stdin();
		ft_printf(input);
		hash(input);
	}
	else if (ft_strcmp((argv[i]), "-q") == 0)
		args->flag_q = 1;
	else if (ft_strcmp((argv[i]), "-r") == 0)
		args->flag_r = 1;
	else if (ft_strcmp((argv[i]), "-s") == 0)
		i = flag_s(argc, argv, i, args);
	else
	{
		// ft_printf("arg: %s\n", argv[i]);//
		read_file(argv[i], args);
	}
	return (++i);
}

void	read_args(int argc, char **argv, t_args *args)
{
	int i;
	char *input;

	i = 2;
	input = NULL;
	if (argc == 1)
		print_usage();
	else
	{
		// if (ft_strcmp((argv[1]), "md5") == 0)
		// 	args->md5 = 1;
		// else if (ft_strcmp((argv[1]), "sha256") == 0)
		// 	args->sha256 = 1;
		// else
		// 	print_usage();
		if (!((ft_strcmp((argv[1]), "md5") == 0) || (ft_strcmp((argv[1]), "sha256") == 0)))
			print_usage();
		g_cmd = argv[1];
		if (argc == 2)
			hash(read_stdin());
		else
		{
			while (i < argc)
				i = read_arg(argc, argv, args, i);
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
	// ft_printf("args.md5: %d\n", args.md5);//rm!!!
	// ft_printf("args.sha256: %d\n", args.sha256);//rm!!!
	// ft_printf("\n\nargs.flag_p: %d\n", args.flag_p);//rm!!!
	// ft_printf("args.flag_q: %d\n", args.flag_q);//rm!!!
	// ft_printf("args.flag_r: %d\n", args.flag_r);//rm!!!
	// ft_printf("args.flag_s: %d\n", args.flag_s);//rm!!!
	// if (args.md5)//
	// 	md5(&args);
	// 	// ft_printf("OH HI\n");//
	// else if (args.sha256)//
	// 	ft_printf("sha256\n");//

	return (0);
}

// flag: -s "string1" -s "string2"
// file as direct argument: ./ft_ssl md5 file
// standard in: echo "string" | ./ft_ssl md5