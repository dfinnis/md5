/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 00:00:00 by dfinnis           #+#    #+#             */
/*   Updated: 2020/10/01 00:00:00 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "../libft/ft_printf/ft_printf.h"
# include "commands_map.h"
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>

/*
**		global command function pointer
*/
void			(*g_cmd_func)(char *);
unsigned long	g_bitlen;

enum			e_bufs
{
	A, B, C, D, E, F, G, I, WORD = 4, TMP = 6
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
void			read_command(char *cmd, t_args *args);

/*
**		read.c
*/
void			read_file(char *filepath, t_args *args);
void			read_stdin(int flag_p);
void			stdin_cmd(t_args *args);

/*
**		read_stdin.c
*/
int				read_fd(const int fd, char **line);

/*
**		print.c
*/
void			error_exit(char *err_msg);
void			print_usage();
void			print_prefix(char *input, t_args *args);
void			print_suffix(char *input, t_args *args);

/*
**		md5_chunk.c
*/
void			md5_chunk(uint32_t hash[4], uint8_t *padded, size_t chunk);

/*
**		sha256.c
*/
void			sha224_256(char *input, int algo);

/*
**		sha256_chunk.c
*/
void			sha256_chunk(uint32_t hash[8], uint32_t *padded, size_t chunk);

/*
**		sha512.c
*/
void			sha384_512(char *input, int algo);

/*
**		sha512_chunk.c
*/
void			sha512_chunk(uint64_t hash[8], uint64_t *padded, size_t chunk);

#endif
