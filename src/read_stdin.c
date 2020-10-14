#include "../inc/ft_ssl.h"

void	read_stdin(int flag_p)
{
	char	*input;
	int		error;

	input = NULL;
	if ((error = read_fd(0, &input) == -1))
	{
		ft_dprintf(2, "error reading stdin\n", error);
		exit(1);
	}
	g_len *= 8;
	if (flag_p)
		ft_printf(input);
	g_cmd_func(input);
	ft_printf("\n");
}

void	stdin_cmd(t_args *args)
{
	char	*input;
	int		error;

	ft_putstr("FT_SSL> ");
	input = NULL;
	if ((error = get_next_line(0, &input) == -1))
	{
		ft_dprintf(2, "error reading stdin\n", error);
		exit(1);
	}
	if (ft_strcmp(input, "quit") == 0)
		exit(0);
	if (ft_strcmp(input, "") == 0)
		stdin_cmd(args);
	read_command(input, args);
	if (g_cmd_func == NULL)
		stdin_cmd(args);
	else
		read_stdin(0);
}
