#include "../inc/ft_ssl.h"

static void		print_digest(/*uint32_t hash[8]*/)
{
	ft_printf("!SHA DIGEST!!!\n");//
}

void	init_hash(uint32_t hash[8])
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

void	sha256(char *input)
{
	ft_printf("sha input: %s\n", input);//rm!!!

	// uint8_t			*padded;
	uint32_t		hash[8];
	// size_t			chunk;
	// unsigned int	msg_len;

	// padded = pad(input, &msg_len);
	init_hash(hash);

	ft_printf("\n");
	int j = 0;//
	while (j < 8)//
	{//
		ft_printf("hash[%d]: 0x%x\n", j, hash[j]);//
		j++;//
	}//

	// chunk = 0;
	// while (chunk < msg_len)
		// digest_chunk(hash, padded, chunk++);
	print_digest(/*hash*/);
}