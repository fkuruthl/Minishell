/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:07:19 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:31:49 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_buffer;
	const unsigned char	*src_buffer;
	size_t				i;

	if (!dest && !src)
		return (NULL);
	dest_buffer = (unsigned char *)dest;
	src_buffer = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dest_buffer[i] = src_buffer[i];
		i++;
	}
	return (dest);
}
