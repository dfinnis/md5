/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 00:00:00 by dfinnis           #+#    #+#             */
/*   Updated: 2020/10/01 00:00:00 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

static uint8_t	*pad(char *input, uint32_t *msg_len)
{
	unsigned long	i;
	uint8_t			*padded;

	(*msg_len) = g_bitlen + 1;
	while ((*msg_len) % 512 != 448)
		(*msg_len)++;
	(*msg_len) = ((*msg_len) + 64) / 8;
	if (!(padded = (uint8_t *)malloc(sizeof(uint8_t) * (*msg_len))))
		error_exit("memory allocation failed");
	i = -1;
	while (++i < g_bitlen / 8)
		padded[i] = input[i];
	padded[i] = 128;
	while (++i < (*msg_len))
		padded[i] = 0;
	i = (*msg_len) - 9;
	while (++i < (*msg_len))
	{
		padded[i] = g_bitlen % 256;
		g_bitlen /= 256;
	}
	(*msg_len) /= 64;
	return (padded);
}

static void		print_digest(uint32_t hash[4])
{
	uint8_t	*bytes;
	int		i;

	bytes = (uint8_t*)&hash[0];
	i = 0;
	while (i < 16)
		ft_printf("%02x", bytes[i++]);
}

void			md5(char *input)
{
	uint8_t			*padded;
	uint32_t		hash[4];
	size_t			chunk;
	unsigned int	msg_len;

	padded = pad(input, &msg_len);
	hash[A] = 0x67452301;
	hash[B] = 0xEFCDAB89;
	hash[C] = 0x98BADCFE;
	hash[D] = 0x10325476;
	chunk = 0;
	while (chunk < msg_len)
		md5_chunk(hash, padded, chunk++);
	free(padded);
	print_digest(hash);
}
