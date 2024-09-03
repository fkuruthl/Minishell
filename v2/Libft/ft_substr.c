/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:07:19 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:33:20 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*makebuf(char const *s, unsigned int start, size_t len, size_t slen)
{
	char	*buffer;
	size_t	remainder;

	remainder = 0;
	while (s[start + remainder] != '\0')
		remainder++;
	if (start + len > slen)
	{
		buffer = malloc((remainder + 1) * sizeof(*buffer));
		if (!buffer)
			return (NULL);
	}
	else
	{
		buffer = malloc((len + 1) * sizeof(*buffer));
		if (!buffer)
			return (NULL);
	}
	return (buffer);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*buffer;
	size_t	i;
	size_t	slen;

	if (!s)
		return (NULL);
	i = 0;
	slen = ft_strlen(s);
	if (start > slen)
		return (ft_strdup(""));
	buffer = makebuf(s, start, len, slen);
	if (!buffer)
		return (NULL);
	while (*(s + start) && i < len)
	{
		buffer[i++] = *((s++) + start);
	}
	buffer[i] = '\0';
	return (buffer);
}
