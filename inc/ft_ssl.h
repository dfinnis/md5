
#ifndef FT_SSL_H
# define FT_SSL_H

# include "../libft/ft_printf/ft_printf.h"
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>

char	*g_cmd;

enum		e_bufs
{
	A, B, C, D, WORD, F, TMP
};

typedef struct			s_args
{
	int					flag_p;
	int					flag_q;
	int					flag_r;
	int					flag_s;
}						t_args;

/*
**		ft_ssl.c
*/
// static void	init_ssl(t_args *args);
// int		read_arg(char **argv, t_args *args, int i);
void		print_prefix(char *input, t_args *args);
void		print_suffix(char *input, t_args *args);
void		read_args(int argc, char **argv, t_args *args);
void		print_usage();

/*
**		read.c
*/
int			read_fd(const int fd, char **line);
void		read_file(char *filepath, t_args *args);
char		*read_stdin(void);

/*
**		md5.c
*/
void		md5(/*t_args *args*/);
void		hash(char *input);

/*
**		md5_rotate.c
*/
void		left_rotate_b(uint32_t *buf, size_t round, uint32_t *words);

/*
**		sha.c
*/
void		sha(char *input);

#endif
