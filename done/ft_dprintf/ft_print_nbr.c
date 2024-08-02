/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:07:19 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:29:47 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	num_len(int nb)
{
	int	count;
	int	flag;

	count = 0;
	flag = 0;
	if (nb == -2147483648)
		return (11);
	if (nb < 0)
	{
		nb *= -1;
		flag = 1;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		count++;
	}
	if (flag)
		return (count + 2);
	else
		return (count + 1);
}

static void	put_nbr(int fd, int nb)
{
	if (nb == -2147483648)
	{
		ft_putstr(fd, "-2");
		nb = 147483648;
	}
	if (nb < 0)
	{
		nb *= -1;
		ft_putchar(fd, '-');
	}
	if (nb >= 10)
	{
		put_nbr(fd, nb / 10);
		put_nbr(fd, nb % 10);
	}
	else
	{
		ft_putchar(fd, nb + 48);
	}
}

int	ft_print_nbr(int fd, int nb)
{
	put_nbr(fd, nb);
	return (num_len(nb));
}
