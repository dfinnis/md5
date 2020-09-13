#include "../inc/ft_ssl.h"

void	md5(char *input/*t_args *args*/)
{
	// ft_printf("MD5!!!!!!\n");//
	// ft_printf("args.md5: %d\n", args->md5);//rm!!!
	ft_printf("HASH md5 input: %s\n", input);//rm!!!
}

void	hash(char *input)
{
	// ft_printf("hash input: %s\n", input);//rm!!!
	if (ft_strcmp(g_cmd, "md5") == 0)
		md5(input);
	else if (ft_strcmp(g_cmd, "sha256") == 0)
		sha(input);
}