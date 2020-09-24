#include "../inc/ft_ssl.h"

void			hash(char *input)
{
	if (ft_strcmp(g_cmd, "md5") == 0)
		md5(input);
	else if (ft_strcmp(g_cmd, "sha256") == 0)
		sha(input);
}
