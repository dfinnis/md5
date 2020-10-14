#include "../inc/ft_ssl.h"

void	sha224(char *input)
{
	sha224_256(input, 224);
}

void	sha256(char *input)
{
	sha224_256(input, 256);
}
