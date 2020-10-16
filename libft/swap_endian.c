/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_endian.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfinnis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 00:00:00 by dfinnis           #+#    #+#             */
/*   Updated: 2020/10/01 00:00:00 by dfinnis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint32_t	swap_endian(uint32_t before)
{
	uint32_t after;

	after = 0;
	after |= (before & 0x000000ff) << 24;
	after |= (before & 0x0000ff00) << 8;
	after |= (before & 0x00ff0000) >> 8;
	after |= (before & 0xff000000) >> 24;
	return (after);
}

uint64_t	swap_endian64(uint64_t before)
{
	uint64_t after;

	after = 0;
	after |= (before & 0xff00000000000000) >> 56;
	after |= (before & 0x00ff000000000000) >> 40;
	after |= (before & 0x0000ff0000000000) >> 24;
	after |= (before & 0x000000ff00000000) >> 8;
	after |= (before & 0x00000000ff000000) << 8;
	after |= (before & 0x0000000000ff0000) << 24;
	after |= (before & 0x000000000000ff00) << 40;
	after |= (before & 0x00000000000000ff) << 56;
	return (after);
}
