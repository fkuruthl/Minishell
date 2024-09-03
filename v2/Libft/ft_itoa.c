/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:07:19 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:31:04 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digit_counter(int n)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (n < 0)
	{
		n *= -1;
		flag = 1;
	}
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	if (flag == 1)
		return (i + 2);
	else
		return (i + 1);
}

static void	positive_copy(char *buffer, int n, int digits)
{
	int		i;

	i = 0;
	buffer[digits] = '\0';
	i++;
	while (n >= 10)
	{
		buffer[digits - i] = (n % 10) + 48;
		n = n / 10;
		i++;
	}
	buffer[digits - i] = n + 48;
}

static void	negative_copy(char *buffer, int n, int digits)
{
	int		i;

	i = 0;
	n *= -1;
	buffer[digits] = '\0';
	i++;
	while (n >= 10)
	{
		buffer[digits - i] = (n % 10) + 48;
		n = n / 10;
		i++;
	}
	buffer[digits - i] = n + 48;
	i++;
	buffer[digits - i] = '-';
}

char	*ft_itoa(int n)
{
	char	*buffer;
	int		digits;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else
		digits = digit_counter(n);
	if (n < 0)
	{
		buffer = (char *)malloc((digits + 1) * sizeof(*buffer));
		if (buffer == NULL)
			return (NULL);
		negative_copy(buffer, n, digits);
	}
	else
	{
		buffer = (char *)malloc((digits + 1) * sizeof(*buffer));
		if (buffer == NULL)
			return (NULL);
		positive_copy(buffer, n, digits);
	}
	return (buffer);
}
