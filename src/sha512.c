#include "../inc/ft_ssl.h"

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
}

static void		print_digest(uint64_t hash[8], int algo)
{
	int i;

	i = 0;
	while (i < 8)
	{
		ft_printf("%016llx", hash[i++]);
		if (i >= 6 && algo == 384)
			break ;
	}
}

void	sha384_512(char *input, int algo)
{
	uint64_t	hash[8];

	ft_printf("oh hi 384: %s\n", input);//
	init_hash(hash, algo);
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
