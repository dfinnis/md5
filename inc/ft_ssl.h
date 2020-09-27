
#ifndef FT_SSL_H
# define FT_SSL_H

# include "../libft/ft_printf/ft_printf.h"
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>

/*
**		global command function dispatcher
*/
void			(*g_cmd_func)(char *);

enum			e_bufs
{
	A, B, C, D, WORD, F, TMP
};

typedef struct	s_args
{
	char		*command;
	int			flag_q;
	int			flag_r;
	int			flag_s;
	int			first;
}				t_args;

/*
**		ft_ssl.c
*/
void			print_prefix(char *input, t_args *args);
void			print_suffix(char *input, t_args *args);
void			read_args(int argc, char **argv, t_args *args);
void			print_usage();

/*
**		read.c
*/
void			read_file(char *filepath, t_args *args);
char			*read_stdin(void);

/*
**		md5.c
*/
void			md5(char *input);

/*
**		md5_rotate.c
*/
void			rotate_left_b(uint32_t *buf, size_t round, uint32_t *words);

/*
**		sha.c
*/
void			sha256(char *input);

#endif
