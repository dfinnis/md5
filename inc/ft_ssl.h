
#ifndef FT_SSL_H
# define FT_SSL_H

# include "../libft/ft_printf/ft_printf.h"
# include <fcntl.h>
# include <errno.h>


typedef struct			s_args
{
	int					md5;
	int					sha256;
	int					flag_p;
	int					flag_q;
	int					flag_r;
	int					flag_s;
}						t_args;

/*
**		ft_ssl.c
*/
// static void	init_ssl(t_args *args);
int			read_arg(char **argv, t_args *args, int i);
void		read_args(int argc, char **argv, t_args *args);
void		print_usage();

/*
**		md5.c
*/
void	md5(t_args *args);

#endif
