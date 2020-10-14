#include "../inc/ft_ssl.h"

static uint64_t g_k[] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f,
	0xe9b5dba58189dbbc, 0x3956c25bf348b538, 0x59f111f1b605d019,
	0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242,
	0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
	0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 0x2de92c6f592b0275,
	0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f,
	0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc,
	0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6,
	0x92722c851482353b, 0xa2bfe8a14cf10364, 0xa81a664bbc423001,
	0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
	0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99,
	0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc,
	0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915,
	0xc67178f2e372532b, 0xca273eceea26619c, 0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba,
	0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
	0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

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

uint64_t	swap_endianness64(uint64_t before)
{
	uint64_t after;

	after = 0;
	after |= (before & 0xff00000000000000) >> 56;
	after |= (before & 0x00ff000000000000) >> 40;
	after |= (before & 0x0000ff0000000000) >> 24;
	after |= (before & 0x000000ff00000000) >> 8;
	after |= (before & 0x00000000ff000000) << 8;
	after |= (before & 0x0000000000ff0000) << 24;
	after |= (before & 0x000000000000ff00) << 40;
	after |= (before & 0x00000000000000ff) << 56;
	return (after);
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

uint64_t	rotate64_right(uint64_t x, uint64_t n)
{
	return ((x >> n) | (x << (64 - n)));
}

static void		operations(uint64_t *buf, uint64_t *words, size_t i)
{
	uint64_t ch;
	uint64_t maj;
	uint64_t s[2];
	uint64_t tmp[2];

	ch = (buf[E] & buf[F]) ^ ((~buf[E]) & buf[G]);
	maj = (buf[A] & buf[B]) ^ (buf[A] & buf[C]) ^ (buf[B] & buf[C]);
	s[0] = rotate64_right(buf[A], 28) ^ rotate64_right(buf[A], 34) ^
	rotate64_right(buf[A], 39);
	s[1] = rotate64_right(buf[E], 14) ^ rotate64_right(buf[E], 18) ^
	rotate64_right(buf[E], 41);
	tmp[0] = buf[I] + s[1] + ch + g_k[i] + words[i];
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

static void		extend(uint64_t *words, size_t i)
{
	uint64_t s0;
	uint64_t s1;

	s0 = rotate64_right(words[i - 15], 1) ^ rotate64_right(words[i - 15], 8) ^
	(words[i - 15] >> 7);
	s1 = rotate64_right(words[i - 2], 19) ^ rotate64_right(words[i - 2], 61)
	^ (words[i - 2] >> 6);
	words[i] = words[i - 16] + s0 + words[i - 7] + s1;
}

static void		digest_chunk(uint64_t hash[8], uint64_t *padded, size_t chunk)
{
	uint64_t	*words;
	size_t		round;
	uint64_t	buf[8];
	int			i;

	if ((words = ft_calloc(80, 64)) == NULL)
	{
		ft_dprintf(2, "Memory allocation failure\n");
		exit(EXIT_FAILURE);
	}
	ft_memcpy(words, &padded[chunk * 16], 1024);
	round = 16;
	while (round < 80)
		extend(words, round++);
	i = -1;
	while (++i < 8)
		buf[i] = hash[i];
	round = 0;
	while (round < 80)
		operations(buf, words, round++);
	i = -1;
	while (++i < 8)
		hash[i] += buf[i];
	free(words);
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

void	sha384_512(char *input, int algo)
{
	uint64_t	*padded;
	uint64_t	hash[8];
	size_t		msg_len;
	size_t		chunk;

	padded = pad(input, &msg_len);
	init_hash(hash, algo);
	chunk = 0;
	while (chunk < msg_len)
		digest_chunk(hash, padded, chunk++);
	free(padded);
	print_digest(hash, algo);
}

void	sha384(char *input)
{
	sha384_512(input, 384);
}

void	sha512(char *input)
{
	sha384_512(input, 512);
}

void	sha512224(char *input)
{
	sha384_512(input, 512224);
}

void	sha512256(char *input)
{
	sha384_512(input, 512256);
}
