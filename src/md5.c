#include "../inc/ft_ssl.h"

static uint8_t	*padding(char *input, uint32_t *msg_len)
{
	unsigned long	strlen8;
	unsigned long	i;
	uint8_t			*padded;

	i = -1;
	strlen8 = ft_strlen(input) * 8;
	(*msg_len) = strlen8 + 1;
	while ((*msg_len) % 512 != 448)
		(*msg_len)++;
	(*msg_len) = ((*msg_len) + 64) / 8;
	if (!(padded = (uint8_t *)malloc(sizeof(uint8_t) * (*msg_len))))//free!!!
		ft_printf("Error: memory allocation failed\n");//EXIT!!!!
	while (++i < strlen8 / 8)
		padded[i] = input[i];
	padded[i] = 128;
	while (++i < (*msg_len))
		padded[i] = 0;
	i = (*msg_len) - 9;
	while (++i < (*msg_len))
	{
		padded[i] = strlen8 % 256;
		strlen8 /= 256;
	}
	(*msg_len) /= 64;
	return (padded);
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

static void		process_chunk(uint32_t hash[4], uint8_t *padded, size_t chunk)
{
	uint32_t		buf[7];
	uint32_t		*words;
	size_t			round;

	words = (uint32_t*)(padded + chunk * 64);
	buf[A] = hash[A];
	buf[B] = hash[B];
	buf[C] = hash[C];
	buf[D] = hash[D];
	round = 0;
	while (round < 64)
		rounds(buf, words, round++);
	hash[A] += buf[A];
	hash[B] += buf[B];
	hash[C] += buf[C];
	hash[D] += buf[D];
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

	chunk = 0;
	padded = padding(input, &msg_len);
	hash[A] = 0x67452301;
	hash[B] = 0xEFCDAB89;
	hash[C] = 0x98BADCFE;
	hash[D] = 0x10325476;
	while (chunk < msg_len)
		process_chunk(hash, padded, chunk++);
	print_digest(hash);
}

void			hash(char *input)
{
	if (ft_strcmp(g_cmd, "md5") == 0)
		md5(input);
	else if (ft_strcmp(g_cmd, "sha256") == 0)
		sha(input);
}
