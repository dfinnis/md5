/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 00:00:00 by dfinnis           #+#    #+#             */
/*   Updated: 2020/10/01 00:00:00 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

void		error_exit(char *err_msg)
{
	ft_dprintf(2, "Error: %s\n", err_msg);
	exit(1);
}

void		print_usage(void)
{
	ft_putstr("\nStandard commands:\n");
	ft_putstr("\n");
	ft_putstr("Message Digest commands:\n");
	ft_putstr("md5\n");
	ft_putstr("sha224\n");
	ft_putstr("sha256\n");
	ft_putstr("sha384\n");
	ft_putstr("sha512\n");
	ft_putstr("sha512224\n");
	ft_putstr("sha512256\n");
	ft_putstr("\n");
	ft_putstr("Cipher commands:\n");
	ft_putstr("\n");
}

void		print_prefix(char *input, t_args *args)
{
	unsigned long i;
	unsigned long len;

	if (!args->flag_q && !args->flag_r)
	{
		i = 0;
		len = ft_strlen(args->command);
		while (i < len)
			ft_printf("%c", ft_toupper(args->command[i++]));
		if (args->flag_s)
			ft_printf(" (\"%s\") = ", input);
		else
			ft_printf(" (%s) = ", input);
	}
}

void		print_suffix(char *input, t_args *args)
{
	if (args->flag_r && !args->flag_q)
	{
		if (args->flag_s)
			ft_printf(" \"%s\"", input);
		else
			ft_printf(" %s", input);
	}
	ft_printf("\n");
}
