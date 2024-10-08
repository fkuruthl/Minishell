/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_address.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:07:19 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:29:37 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	address_len(unsigned long long int c)
{
	int	len;

	len = 0;
	if (c == 0)
		return (ft_strlen("0x0"));
	while (c >= 16)
	{
		c = c / 16;
		len++;
	}
	return (len + 1);
}

static void	put_address(int fd, unsigned long long int c)
{
	const char	*set;

	set = "0123456789abcdef";
	if (c >= 16)
	{
		put_address(fd, c / 16);
		put_address(fd, c % 16);
	}
	else
	{
		ft_putchar(fd, set[c % 16]);
	}
}

int	ft_print_address(int fd, unsigned long long int c)
{
	if (c == 0)
	{
		ft_putstr(fd, "0x0");
		return (ft_strlen("0x0"));
	}
	ft_putstr(fd, "0x");
	put_address(fd, c);
	return (ft_strlen("0x") + address_len(c));
}
