#include "../inc/ft_ssl.h"

void	print_usage(void)
{
	ft_putstr("\nusage:\t./ft_ssl []");
	// free(eveything);
	exit(1);
}

char	*read_file(char *filepath)
{
	char *input;
	int	error;
	int	fd;

	input = NULL;
	if ((fd = open(filepath, O_RDONLY)) == -1)
	{
		ft_printf("ft_ssl: md5/sha: %s: %s\n", filepath, strerror(errno));/// command md5/sha etc!!!
		//error exit
	}
	// if directory?? deal with!!!
	if ((error = read_fd(fd, &input) == 0))
		ft_printf("error deal with empty file\n", error);// DEAL WITH EMPTY FILE, input = '\0'???!!!
	// ft_printf("error: %d\n", error);//
	// ft_printf("fd: %d\n", fd);//
	// print_usage();??
	return input;
}

void	read_stdin(void)
{
	char *input;
	int	error;

	input = NULL;
	if ((error = read_fd(0, &input) == 0))
		ft_printf("error deal with empty input stdin\n", error);// DEAL WITH EMPTY FILE, input = '\0'???!!!
	ft_printf("input stdin: %s\n", input);//
	// hash(input)!!!!
}

static int	read_arg(int argc, char **argv, t_args *args, int i)
{
	char *input;

	input = NULL;
	if (ft_strcmp((argv[i]), "-p") == 0)
		args->flag_p = 1;
	else if (ft_strcmp((argv[i]), "-q") == 0)
		args->flag_q = 1;
	else if (ft_strcmp((argv[i]), "-r") == 0)
		args->flag_r = 1;
	else if (ft_strcmp((argv[i]), "-s") == 0)
	{
		args->flag_s = 1;// rm??!!
		{
			if (i + 2 > argc)
				ft_printf("Error: no string here!!\n");// EXIT!!!
			input = argv[++i];
			ft_printf("input string: %s\n", input);//
		}
	}
	else
	{
		// ft_printf("arg: %s\n", argv[i]);//
		input = read_file(argv[i]);
		ft_printf("input here: %s\n", input);//
	}
	return (++i);
}

void	read_args(int argc, char **argv, t_args *args)
{
	int i;

	i = 2;
	if (argc == 1)
		print_usage();
	else
	{
		if (ft_strcmp((argv[1]), "md5") == 0)
			args->md5 = 1;
		else if (ft_strcmp((argv[1]), "sha256") == 0)
			args->sha256 = 1;
		else
			print_usage();
		if (argc == 2)
			read_stdin();
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
	ft_printf("args.md5: %d\n", args.md5);//rm!!!
	ft_printf("args.sha256: %d\n", args.sha256);//rm!!!
	ft_printf("args.flag_p: %d\n", args.flag_p);//rm!!!
	ft_printf("args.flag_q: %d\n", args.flag_q);//rm!!!
	ft_printf("args.flag_r: %d\n", args.flag_r);//rm!!!
	ft_printf("args.flag_s: %d\n", args.flag_s);//rm!!!
	if (args.md5)//
		md5(&args);
		// ft_printf("OH HI\n");//
	else if (args.sha256)//
		ft_printf("sha256\n");//

	return (0);
}

// flag: -s "string1" -s "string2"
// file as direct argument: ./ft_ssl md5 file
// standard in: echo "string" | ./ft_ssl md5