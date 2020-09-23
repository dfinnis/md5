#include "../inc/ft_ssl.h"

const uint32_t	g_shift[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

// for i from 0 to 63 do
//		g_sines[i] := floor(232 × abs (sin(i + 1)))
const uint32_t	g_sine[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static uint8_t	*padding(char *input, uint32_t *msg_len)
{
	unsigned long	strlen8;
	unsigned int	bitlen;
	unsigned long	i;
	uint8_t			*padded;

	i = -1;
	padded = NULL;
	strlen8 = ft_strlen(input) * 8;
	bitlen = strlen8 + 1;
	while (bitlen % 512 != 448)
		bitlen++;
	bitlen = (bitlen + 64) / 8;
	(*msg_len) = bitlen;
	if (!(padded = (uint8_t *)malloc(sizeof(uint8_t) * bitlen)))///free me!!!
		ft_printf("Error: memory allocation failed\n");//EXIT!!!!
	while (++i < strlen8 / 8)
		padded[i] = input[i];
	padded[i] = 128;
	while (++i < bitlen)////////////////:thongking face!!!!!!!!!!!!!!!!!
		padded[i] = 0;
	i = bitlen - 9;
	while (++i < bitlen)
	{
		padded[i] = strlen8 % 256;
		strlen8 /= 256;
	}
	return (padded);
}

uint32_t		leftrotate(uint32_t x, uint32_t n)
{
	return ((x << n) | (x >> (32 - n)));
}

static void		left_rotate_b(uint32_t *buf, size_t round, uint32_t *words)
{
	buf[B] += leftrotate((buf[F] + buf[A] + g_sine[round] + words[buf[WORD]]),
							g_shift[round]);
}

static void		rounds(uint32_t *buf, uint32_t *words, size_t round)
{
	if (round < 16)
	{
		buf[WORD] = round;
		buf[F] = (buf[B] & buf[C]) | ((~buf[B]) & buf[D]);
	}
	else if (round < 32)
	{
		buf[WORD] = (5 * round + 1) % 16;
		buf[F] = (buf[D] & buf[B]) | ((~buf[D]) & buf[C]);
	}
	else if (round < 48)
	{
		buf[WORD] = (3 * round + 5) % 16;
		buf[F] = buf[B] ^ buf[C] ^ buf[D];
	}
	else
	{
		buf[WORD] = (7 * round) % 16;
		buf[F] = buf[C] ^ (buf[B] | (~buf[D]));
	}
	buf[TMP] = buf[D];
	buf[D] = buf[C];
	buf[C] = buf[B];
	left_rotate_b(buf, round, words);
	buf[A] = buf[TMP];
}

void			process_chunk(uint32_t hash[4], uint8_t *padded, size_t chunk)
{
	uint32_t		buf[7];
	uint32_t		*words;
	size_t			round;

	buf[A] = hash[A];
	buf[B] = hash[B];
	buf[C] = hash[C];
	buf[D] = hash[D];
	words = (uint32_t*)(padded + chunk);
	round = 0;
	while (round < 64)
		rounds(buf, words, round++);
	hash[A] += buf[A];
	hash[B] += buf[B];
	hash[C] += buf[C];
	hash[D] += buf[D];
}

void			print_digest(uint32_t hash[4])
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

	chunk = 0;
	padded = padding(input, &msg_len);
	hash[A] = 0x67452301;
	hash[B] = 0xEFCDAB89;
	hash[C] = 0x98BADCFE;
	hash[D] = 0x10325476;
	while (chunk < msg_len)
	{
		process_chunk(hash, padded, chunk);
		chunk += 64;
	}
	print_digest(hash);
}

void			hash(char *input)
{
	if (ft_strcmp(g_cmd, "md5") == 0)
		md5(input);
	else if (ft_strcmp(g_cmd, "sha256") == 0)
		sha(input);
}
