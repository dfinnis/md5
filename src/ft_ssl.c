#include "../inc/ft_ssl.h"

void	print_usage()
{
	ft_putstr("\nusage:\t./ft_ssl []");
	// free(eveything);
	exit(1);
}

int		read_flag(char **argv, t_args *args, int i)
{
	if (ft_strcmp((argv[i]), "-p") == 0)
		args->flag_p = 1;
	else if (ft_strcmp((argv[i]), "-q") == 0)
		args->flag_q = 1;
	else if (ft_strcmp((argv[i]), "-r") == 0)
		args->flag_r = 1;
	else if (ft_strcmp((argv[i]), "-s") == 0)
		args->flag_s = 1;
	else
		print_usage();
	return (++i);
}

void	read_args(int argc, char **argv, t_args *args)
{
	int i;

	i = 2;
	if (argc == 1)
		print_usage();
	else
		if (ft_strcmp((argv[1]), "md5") == 0)
			args->md5 = 1;
		else if (ft_strcmp((argv[1]), "sha256") == 0)
			args->sha256 = 1;
		else
			print_usage();
		if (argc > 2)
			while (i < argc)
				i = read_flag(argv, args, i);
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


	return (0);
}
