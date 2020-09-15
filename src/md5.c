#include "../inc/ft_ssl.h"

static uint8_t	*padding(char *input)
{
	long	strlen8;
	long	bitlen;
	long	i;
	uint8_t	*padded;

	i = -1;
	padded = NULL;
	strlen8 = ft_strlen(input) * 8;
	bitlen = strlen8 + 1;
	while (bitlen % 512 != 448)
		bitlen++;
	bitlen = (bitlen + 64) / 8;
	if (!(padded = (uint8_t *)malloc(sizeof(uint8_t) * bitlen)))///free me!!!
		ft_printf("Error: memory allocation failed\n");//EXIT!!!!
	while (++i < strlen8 / 8)
		padded[i] = input[i];
	padded[i++] = 128;
	while (i < bitlen)
		padded[i++] = 0;
	while (i-- > bitlen - 8)
	{
		padded[i] = strlen8 % 256;
		strlen8 /= 256;
	}
	return (padded);
}

void			md5(char *input)
{
	uint8_t			*padded;

	padded = NULL;
	padded = padding(input);
	ft_printf("padded: %s\n", padded);//
}

void			hash(char *input)
{
	if (ft_strcmp(g_cmd, "md5") == 0)
		md5(input);
	else if (ft_strcmp(g_cmd, "sha256") == 0)
		sha(input);
}
