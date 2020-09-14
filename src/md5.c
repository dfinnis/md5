#include "../inc/ft_ssl.h"

void 	padding(char *input)
{
	unsigned long	len;
	unsigned long	strlen;
	unsigned long	strlen8;
	unsigned long	i;
	// unsigned long	eight;//
	uint8_t			*padded;

	i = 0;
	// eight = 8;//
	padded = NULL;
	ft_printf("padding input: %s\n", input);//
	strlen = ft_strlen(input);
	strlen8 = strlen * 8;
	len = strlen * 8 + 1;
	// ft_printf("len: %d\n", len);//
	while (len % 512 != 448)
		len++;
	len += 64;
	// ft_printf("len mod: %d\n", len);//
	// ft_printf("len mod - 64: %d\n", len - 64);//
	if (!(padded = (uint8_t *)malloc(sizeof(uint8_t) * len / 8)))///free me!!!
		ft_printf("Error: memory allocation failed\n");//EXIT!!!!
	while (i < strlen)
	{
		padded[i] = input[i];
		i++;
	}
	padded[i++] = 128;
	while (i < len/8)////necessary??
		padded[i++] = 0;////necessary??
	// ft_printf("i: %d\n", i);//
	while (i-- > len/8-8)
	{
		// ft_printf("i: %d, strlen8: %d\n", i, strlen8);//
		// ft_printf("strlen8 %% 256: %d\n", strlen8 % 256);//
		padded[i] = strlen8 % 256;
		strlen8 /= 256;
	}

	ft_printf("padded: %s\n", padded);//
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
	// ft_printf("padded[len/8-2]: %d\n", padded[len/8 - 2]);//
	// ft_printf("padded[len/8-1]: %d\n", padded[len/8 - 1]);//

	// ft_printf("padded[len/8]: %d\n", padded[len/8]);//
	// ft_printf("padded[62]: %d\n", padded[62]);//
	// ft_printf("padded[511]: %d\n", padded[511]);//
	// ft_printf("padded[5122]: %c\n", padded[5122]);//
}

void	md5(char *input/*t_args *args*/)
{
	// ft_printf("args.md5: %d\n", args->md5);//
	// ft_printf("HASH md5 input: %s\n", input);//
	padding(input);
}

void	hash(char *input)
{
	// ft_printf("hash input: %s\n", input);//rm!!!
	if (ft_strcmp(g_cmd, "md5") == 0)
		md5(input);
	else if (ft_strcmp(g_cmd, "sha256") == 0)
		sha(input);
}