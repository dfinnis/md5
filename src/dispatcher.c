#include "../inc/ft_ssl.h"

// const int	g_command_int = 0;

// const char *g_command[2] = {
// 	"md5", "sha256"
// };

int command_dispatcher(char *input)
{
    // hash_function *command[2] = {
    //     md5,
    //     sha256
    // };

	ft_printf("\ninput: %s\n", input);
    g_command(input);
    return 0; 
}


void			hash(char *input)
{
	if (ft_strcmp(g_cmd, "md5") == 0)
		md5(input);
	else if (ft_strcmp(g_cmd, "sha256") == 0)
		sha256(input);
	command_dispatcher(input);
}
