
#ifndef FT_SSL_H
# define FT_SSL_H

# include "../libft/ft_printf/ft_printf.h"
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>

char	*g_cmd;

/*
**		function_dispatcher
*/
void 	(*g_command)(char *);
// void 		md5(char *input);
// void		sha256(char *input);

// typedef void hash_function(char *input);


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
void		print_prefix(char *input, t_args *args);
void		print_suffix(char *input, t_args *args);
void		read_args(int argc, char **argv, t_args *args);
void		print_usage();

/*
**		read.c
*/
void		read_file(char *filepath, t_args *args);
char		*read_stdin(void);

/*
**		md5.c
*/
void		md5(char *input);

/*
**		md5_rotate.c
*/
void		rotate_left_b(uint32_t *buf, size_t round, uint32_t *words);

/*
**		dispatcher.c
*/
void		hash(char *input);
void		read_command(char *command);


/*
**		sha.c
*/
void		sha256(char *input);

#endif
