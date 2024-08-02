/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:07:19 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:32:43 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*x1;
	unsigned char	*x2;

	i = 0;
	x1 = (unsigned char *) s1;
	x2 = (unsigned char *) s2;
	while ((x1[i] != '\0' || x2[i] != '\0') && i < n)
	{
		if (x1[i] != x2[i])
			return (x1[i] - x2[i]);
		i++;
	}
	if (i < n)
		return (x1[i] - x2[i]);
	return (0);
}
