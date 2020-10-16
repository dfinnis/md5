/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 00:00:00 by dfinnis           #+#    #+#             */
/*   Updated: 2020/10/01 00:00:00 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_dprintf(int fd, char const *format, ...)
{
	va_list			ap;
	t_print			all;

	va_start(ap, format);
	ft_initialize_print(&all, fd);
	if (!(all.form = ft_strdup(format)))
		ft_error(NULL, all.form);
	while (all.form[all.len] != '\0')
	{
		if (all.form[all.len] == '%')
		{
			all.len++;
			ft_parse(&all, ap);
			ft_read(&all, ap);
			ft_reinitialize(&all);
		}
		else
		{
			ft_putchar_fd(all.form[all.len++], all.fd);
			all.printed++;
		}
	}
	free(all.form);
	va_end(ap);
	return (all.printed);
}
