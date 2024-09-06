/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:08:22 by hsalah            #+#    #+#             */
/*   Updated: 2024/09/06 20:19:19 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_sg_wspace(char c, int state)
{
	if (state != STATE_GENERAL)
		return (0);
	if ((c >= 9 && c <= 13) || (c == 32))
		return (1);
	return (0);
}

static int	get_size(char *str)
{
	int	i;
	int	state;
	int	size;

	i = 0;
	size = 0;
	state = STATE_GENERAL;
	while (str[i])
	{
		while (str[i] && is_sg_wspace(str[i], state))
			state = choose_state2(str[i++], state);
		if (str[i] && state == STATE_GENERAL)
			size++;
		else if (str[i] && state != STATE_GENERAL)
		{
			while (str[i] && state != STATE_GENERAL)
				state = choose_state2(str[i++], state);
			if (str[i])
				size++;
		}
		while (str[i] && !is_sg_wspace(str[i], state))
			state = choose_state2(str[i++], state);
	}
	return (size);
}

static char	**pt_split(char	*str, int state, int size)
{
	int		i;
	char	**buffer;
	int		j;
	int		k;

	i = 0;
	k = 0;
	buffer = (char **)malloc(sizeof(char *) * (size + 1));
	while (str[i])
	{
		if (str[i] && is_sg_wspace(str[i], state))
			state = choose_state2(str[i++], state);
		else
		{
			j = 0;
			while (str[i + j] && !is_sg_wspace(str[i + j], state))
				state = choose_state2(str[i + (j++)], state);
			buffer[k] = (char *)malloc(j + 1);
			ft_strlcpy(buffer[k++], str + i, j + 1);
			i = i + j;
		}
	}
	buffer[size] = NULL;
	return (buffer);
}

char	**split_with_quotes(char *str)
{
	char	**buffer;
	int		i;
	int		size;

	buffer = NULL;
	i = 0;
	if (str[i] == '\0')
	{
		buffer = (char **)malloc(sizeof(char *) * (2));
		buffer[0] = ft_strdup(str);
		buffer[1] = NULL;
	}
	else
	{
		size = get_size(str);
		buffer = pt_split(str, STATE_GENERAL, size);
	}
	return (buffer);
}

void	delete_2d_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
