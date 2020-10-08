
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
unsigned long	g_len;

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

/*
**		read.c
*/
void			read_file(char *filepath, t_args *args);
void			read_stdin(int flag_p);

/*
**		print.c
*/
void			print_usage();
void			print_prefix(char *input, t_args *args);
void			print_suffix(char *input, t_args *args);

/*
**		md5.c
*/
uint8_t			*pad(char *input, uint32_t *msg_len);
void			md5(char *input);

/*
**		md5_rotate.c
*/
void			rotate_left_b(uint32_t *buf, size_t round, uint32_t *words);

/*
**		sha.c
*/
void			sha256(char *input);

const static struct {
	const char	*cmd;
	void		(*func)(char *);
} g_cmd_func_map[] = {
	{ "md5", md5 },
	{ "sha256", sha256 },
};

#endif
