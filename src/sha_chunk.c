
#include "../inc/ft_ssl.h"

static uint32_t g_roots[] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static uint32_t	rotate_right(uint32_t x, uint32_t n)
{
	return ((x >> n) | (x << (32 - n)));
}

static void		extend(uint32_t *w, size_t i)
{
	uint32_t s0;
	uint32_t s1;

	s0 = rotate_right(w[i - 15], 7) ^ rotate_right(w[i - 15], 18) ^
	(w[i - 15] >> 3);
	s1 = rotate_right(w[i - 2], 17) ^ rotate_right(w[i - 2], 19)
	^ (w[i - 2] >> 10);
	w[i] = w[i - 16] + s0 + w[i - 7] + s1;
}

static void		operations(uint32_t *buf, uint32_t *w, size_t i)
{
	uint32_t ch;
	uint32_t maj;
	uint32_t s[2];
	uint32_t tmp[2];

	ch = (buf[E] & buf[F]) ^ ((~buf[E]) & buf[G]);
	maj = (buf[A] & buf[B]) ^ (buf[A] & buf[C]) ^ (buf[B] & buf[C]);
	s[0] = rotate_right(buf[A], 2) ^ rotate_right(buf[A], 13) ^
	rotate_right(buf[A], 22);
	s[1] = rotate_right(buf[E], 6) ^ rotate_right(buf[E], 11) ^
	rotate_right(buf[E], 25);
	tmp[0] = buf[I] + s[1] + ch + g_roots[i] + w[i];
	tmp[1] = s[0] + maj;
	buf[I] = buf[G];
	buf[G] = buf[F];
	buf[F] = buf[E];
	buf[E] = buf[D] + tmp[0];
	buf[D] = buf[C];
	buf[C] = buf[B];
	buf[B] = buf[A];
	buf[A] = tmp[0] + tmp[1];
}

void			sha_chunk(uint32_t hash[8], uint32_t *padded, size_t chunk)
{
	uint32_t	*words;
	size_t		round;
	uint32_t	buf[8];
	int			i;

	if ((words = ft_calloc(64, 32)) == NULL)
	{
		ft_dprintf(2, "Memory allocation failure\n");
		exit(1);
	}
	ft_memcpy(words, &padded[chunk * 16], 512);
	round = 16;
	while (round < 64)
		extend(words, round++);
	i = -1;
	while (++i < 8)
		buf[i] = hash[i];
	round = 0;
	while (round < 64)
		operations(buf, words, round++);
	i = -1;
	while (++i < 8)
		hash[i] += buf[i];
	free(words);
}
