#include "../inc/ft_ssl.h"

uint8_t	*padding(char *input)
{
	long	strlen;
	long	strlen8;
	long	bitlen;
	long	i;
	uint8_t			*padded;

	i = -1;
	padded = NULL;
	// ft_printf("padding input: %s\n", input);//
	strlen = ft_strlen(input);
	strlen8 = strlen * 8;
	bitlen = strlen8 + 1;
	while (bitlen % 512 != 448)
		bitlen++;
	bitlen = (bitlen + 64) / 8;
	if (!(padded = (uint8_t *)malloc(sizeof(uint8_t) * bitlen)))///free me!!!
		ft_printf("Error: memory allocation failed\n");//EXIT!!!!
	while (++i < strlen)
		padded[i] = input[i];
	padded[i++] = 128;
	while (i < bitlen)////necessary??
		padded[i++] = 0;////necessary??
	while (i-- > bitlen-8)
	{
		// ft_printf("i: %d, strlen8: %d\n", i, strlen8);//
		// ft_printf("strlen8 %% 256: %d\n", strlen8 % 256);//
		padded[i] = strlen8 % 256;
		strlen8 /= 256;
	}
	// ft_printf("padded: %s\n", padded);//
	// ft_printf("padded[0]: %c\n", padded[0]);//
	// ft_printf("padded[1]: %c\n", padded[1]);//
	// ft_printf("padded[2]: %c\n", padded[2]);//
	// ft_printf("padded[3]: %c\n", padded[3]);//
	// ft_printf("padded[4]: %c\n", padded[4]);//
	// ft_printf("padded[5]: %d\n", padded[5]);//
	// ft_printf("padded[strlen - 2]: %c\n", padded[strlen - 2]);//
	// ft_printf("padded[strlen - 1]: %d\n", padded[strlen - 1]);//
	// ft_printf("padded[strlen]: %b\n", padded[strlen]);//
	// ft_printf("padded[strlen + 1]: %b\n", padded[strlen + 1]);//
	// ft_printf("\n");//

	// // ft_printf("len: %d\n", len);//
	// ft_printf("len/8: %d\n", len/8);//
	// // ft_printf("len/8-2: %d\n", len/8 - 2);//

	// ft_printf("padded[len]: %d\n", padded[len]);//
	// ft_printf("padded[len/8-1-8]: %d\n", padded[len/8 - 1 - 8]);//
	// ft_printf("padded[len/8-1-7]: %d\n", padded[len/8 - 1 - 7]);//
	// ft_printf("padded[len/8-7]: %d\n", padded[len/8 - 7]);//
	// ft_printf("padded[len/8-6]: %d\n", padded[len/8 - 6]);//
	// ft_printf("padded[len/8-5]: %d\n", padded[len/8 - 5]);//
	// ft_printf("padded[len/8-4]: %d\n", padded[len/8 - 4]);//
	// ft_printf("padded[len/8-3]: %d\n", padded[len/8 - 3]);//
	// ft_printf("padded[bitlen-2]: %d\n", padded[bitlen - 2]);//
	// ft_printf("padded[bitlen-1]: %d\n", padded[bitlen - 1]);//
	// ft_printf("padded[len/8]: %d\n", padded[len/8]);//
	return padded;
}

void	md5(char *input/*t_args *args*/)
{
	uint8_t			*padded;

	padded = NULL;
	// ft_printf("args.md5: %d\n", args->md5);//
	// ft_printf("HASH md5 input: %s\n", input);//
	padded = padding(input);
	ft_printf("padded: %s\n", padded);//
}

void	hash(char *input)
{
	// ft_printf("hash input: %s\n", input);//rm!!!
	if (ft_strcmp(g_cmd, "md5") == 0)
		md5(input);
	else if (ft_strcmp(g_cmd, "sha256") == 0)
		sha(input);
}