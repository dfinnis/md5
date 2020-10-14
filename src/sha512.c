#include "../inc/ft_ssl.h"

static void	init_truncated(uint64_t hash[8], int algo)
{
	if (algo == 512224)
	{
		hash[0] = 0x8c3d37c819544da2;
		hash[1] = 0x73e1996689dcd4d6;
		hash[2] = 0x1dfab7ae32ff9c82;
		hash[3] = 0x679dd514582f9fcf;
		hash[4] = 0x0f6d2b697bd44da8;
		hash[5] = 0x77e36f7304c48942;
		hash[6] = 0x3f9d85a86a1d36c8;
		hash[7] = 0x1112e6ad91d692a1;
	}
	else if (algo == 512256)
	{
		hash[0] = 0x22312194fc2bf72c;
		hash[1] = 0x9f555fa3c84c64c2;
		hash[2] = 0x2393b86b6f53b151;
		hash[3] = 0x963877195940eabd;
		hash[4] = 0x96283ee2a88effe3;
		hash[5] = 0xbe5e1e2553863992;
		hash[6] = 0x2b0199fc2c85b8aa;
		hash[7] = 0x0eb72ddc81c52ca2;
	}
}

static void	init_hash(uint64_t hash[8], int algo)
{
	if (algo == 384)
	{
		hash[0] = 0xcbbb9d5dc1059ed8;
		hash[1] = 0x629a292a367cd507;
		hash[2] = 0x9159015a3070dd17;
		hash[3] = 0x152fecd8f70e5939;
		hash[4] = 0x67332667ffc00b31;
		hash[5] = 0x8eb44a8768581511;
		hash[6] = 0xdb0c2e0d64f98fa7;
		hash[7] = 0x47b5481dbefa4fa4;
	}
	else if (algo == 512)
	{
		hash[0] = 0x6a09e667f3bcc908;
		hash[1] = 0xbb67ae8584caa73b;
		hash[2] = 0x3c6ef372fe94f82b;
		hash[3] = 0xa54ff53a5f1d36f1;
		hash[4] = 0x510e527fade682d1;
		hash[5] = 0x9b05688c2b3e6c1f;
		hash[6] = 0x1f83d9abfb41bd6b;
		hash[7] = 0x5be0cd19137e2179;
	}
	else
		init_truncated(hash, algo);
}

static uint64_t	*pad(char *input, size_t *msg_len)
{
	uint64_t	*padded;
	size_t		i;

	padded = NULL;
	(*msg_len) = ((g_len + 128) / 1024) + 1;
	if ((padded = ft_calloc((*msg_len) * 16, 64)) == NULL)
	{
		ft_dprintf(2, "Memory allocation failure\n");
		exit(1);
	}
	((uint8_t*)padded)[g_len / 8] = 0x80;
	ft_memcpy(padded, input, g_len / 8);
	i = -1;
	while (++i < g_len / 8 + 1)
		padded[i] = swap_endianness64(padded[i]);
	padded[((((*msg_len) * 1024) - 128) / 64) + 1] = g_len;
	g_len = 0;
	return (padded);
}

static void		print_digest(uint64_t hash[8], int algo)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (algo == 512224 && i == 3)
			ft_printf("%08llx", hash[i++] / 0x100000000);
		else
			ft_printf("%016llx", hash[i++]);
		if ((algo == 384 && i >= 6) ||
			((algo == 512224 || algo == 512256) && i >= 4))
			break ;
	}
}

void			sha384_512(char *input, int algo)
{
	uint64_t	*padded;
	uint64_t	hash[8];
	size_t		msg_len;
	size_t		chunk;

	padded = pad(input, &msg_len);
	init_hash(hash, algo);
	chunk = 0;
	while (chunk < msg_len)
		sha512_chunk(hash, padded, chunk++);
	free(padded);
	print_digest(hash, algo);
}
