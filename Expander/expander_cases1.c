/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_cases1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:07:19 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:27:10 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	delpotenvar_len(char *str, int state)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		state = choose_state2(str[i], state);
		if (not_stand_alone(str[i], str[i + 1], state))
		{
			i += 1;
			break ;
		}
		len++;
		i++;
	}
	while (str[i] && trailor_validity(str[i]))
		i++;
	while (str[i++])
		len++;
	return (len);
}

static char	*allocator(char **buffer, int len)
{
	*buffer = (char *)malloc(len + 1);
	if (!(*buffer))
		return (NULL);
	return (*buffer);
}

char	*delpotenvar(char *str, int state)
{
	int		i;
	int		j;
	char	*buffer;
	int		len;

	i = 0;
	len = delpotenvar_len(str, STATE_GENERAL);
	if (!allocator(&buffer, len))
		return (warn_message(), NULL);
	j = 0;
	while (str[i])
	{
		state = choose_state2(str[i], state);
		if (not_stand_alone(str[i], str[i + 1], state))
		{
			i += 1;
			break ;
		}
		buffer[j++] = str[i++];
	}
	while (str[i] && trailor_validity(str[i]))
		i++;
	while (str[i])
		buffer[j++] = str[i++];
	return (buffer[j] = '\0', buffer);
}
