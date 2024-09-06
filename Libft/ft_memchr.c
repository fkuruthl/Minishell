/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:07:19 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:31:41 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*buffer;
	unsigned char		character;
	size_t				i;

	buffer = (unsigned char *) s;
	character = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (buffer[i] == character)
		{
			return (buffer + i);
		}
		i++;
	}
	return (NULL);
}
