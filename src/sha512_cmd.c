#include "../inc/ft_ssl.h"

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
