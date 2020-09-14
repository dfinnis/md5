#include "../inc/ft_ssl.h"

void 	padding(char *input)
{
	unsigned long	len;
	unsigned long	strlen;
	unsigned long	i;
	uint8_t			*padded;

	i = 0;
	padded = NULL;
	ft_printf("padding input: %s\n", input);//
	strlen = ft_strlen(input);
	len = strlen * 8 + 1;
	ft_printf("len: %d\n", len);//
	while (len % 512 != 448)
		len++;
	len += 64;
	ft_printf("len mod: %d\n", len);//
	ft_printf("len mod - 64: %d\n", len - 64);//
	if (!(padded = (uint8_t *)malloc(sizeof(uint8_t) * len)))///free me!!!
		ft_printf("Error: memory allocation failed\n");//EXIT!!!!
	while (i < strlen)
	{
		padded[i] = input[i];
		i++;
	}
	padded[i] = 128;
	ft_printf("padded: %s\n", padded);//
	ft_printf("padded[0]: %c\n", padded[0]);//
	ft_printf("padded[1]: %c\n", padded[1]);//
	ft_printf("padded[2]: %c\n", padded[2]);//
	ft_printf("padded[3]: %c\n", padded[3]);//
	ft_printf("padded[4]: %c\n", padded[4]);//
	ft_printf("padded[5]: %d\n", padded[5]);//
	ft_printf("padded[strlen - 2]: %c\n", padded[strlen - 2]);//
	ft_printf("padded[strlen - 1]: %d\n", padded[strlen - 1]);//
	ft_printf("padded[strlen]: %b\n", padded[strlen]);//
	ft_printf("padded[511]: %d\n", padded[511]);//
	ft_printf("padded[5122]: %c\n", padded[5122]);//
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