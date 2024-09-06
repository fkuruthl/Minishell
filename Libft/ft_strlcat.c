/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:07:19 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:32:31 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	original_destlen;

	if (dest == NULL && size == 0)
		return (ft_strlen(src) + size);
	i = 0;
	j = ft_strlen(dest);
	original_destlen = ft_strlen(dest);
	if (size != 0 && original_destlen < size)
	{
		while (src[i] != '\0' && j < size - 1)
		{
			dest[j] = src[i];
			i++;
			j++;
		}
		dest[j] = '\0';
		return (ft_strlen(src) + original_destlen);
	}
	else
		return (ft_strlen(src) + size);
}
