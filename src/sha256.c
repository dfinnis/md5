/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 00:00:00 by dfinnis           #+#    #+#             */
/*   Updated: 2020/10/01 00:00:00 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

static void		init_hash(uint32_t hash[8], int algo)
{
	if (algo == 256)
	{
		hash[0] = 0x6a09e667;
		hash[1] = 0xbb67ae85;
		hash[2] = 0x3c6ef372;
		hash[3] = 0xa54ff53a;
		hash[4] = 0x510e527f;
		hash[5] = 0x9b05688c;
		hash[6] = 0x1f83d9ab;
		hash[7] = 0x5be0cd19;
	}
	else
	{
		hash[0] = 0xc1059ed8;
		hash[1] = 0x367cd507;
		hash[2] = 0x3070dd17;
		hash[3] = 0xf70e5939;
		hash[4] = 0xffc00b31;
		hash[5] = 0x68581511;
		hash[6] = 0x64f98fa7;
		hash[7] = 0xbefa4fa4;
	}
}

static uint32_t	*pad(char *input, size_t *msg_len)
{
	uint32_t	*padded;
	size_t		i;

	padded = NULL;
	(*msg_len) = ((g_len + 64) / 512) + 1;
	if ((padded = ft_calloc((*msg_len) * 16, 32)) == NULL)
		error_exit("memory allocation failure");
	ft_memcpy(padded, input, g_len / 8);
	((uint8_t*)padded)[g_len / 8] = 0x80;
	i = -1;
	while (++i < g_len / 8 + 1)
		padded[i] = swap_endianness(padded[i]);
	padded[((((*msg_len) * 512) - 64) / 32) + 1] = g_len;
	g_len = 0;
	return (padded);
}

static void		print_digest(uint32_t hash[8], int algo)
{
	int i;

	i = 0;
	while (i < 8)
	{
		ft_printf("%08x", hash[i++]);
		if (i == 7 && algo == 224)
			break ;
	}
}

void			sha224_256(char *input, int algo)
{
	uint32_t	*padded;
	uint32_t	hash[8];
	size_t		chunk;
	size_t		msg_len;

	padded = pad(input, &msg_len);
	init_hash(hash, algo);
	chunk = 0;
	while (chunk < msg_len)
		sha256_chunk(hash, padded, chunk++);
	free(padded);
	print_digest(hash, algo);
}
