/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASTree_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:28:36 by hsalah            #+#    #+#             */
/*   Updated: 2024/09/04 09:29:15 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_node_type(t_ASTree *node, t_nodeType nodeType)
{
	if (node == NULL)
		return ;
	node->type = nodeType;
}

void	set_node_data(t_ASTree *node, char *data)
{
	if (node == NULL)
		return ;
	node->data = data;
}

void	attach_branch(t_ASTree *node, t_ASTree *left_n, t_ASTree *right_n)
{
	if (!node)
		return ;
	node->left = left_n;
	node->right = right_n;
}

t_ASTree	*copy_node(t_ASTree *src)
{
	t_ASTree	*dest;
	int			len;

	if (src)
	{
		dest = (t_ASTree *)malloc(sizeof(*dest));
		if (!dest)
			return (warn_message(), NULL);
		dest->left = copy_node(src->left);
	}
	else
		return (NULL);
	dest->right = copy_node(src->right);
	len = ft_strlen(src->data);
	dest->data = (char *)malloc(len + 1);
	if (!(dest->data))
		return (delete_node(dest), warn_message(), NULL);
	ft_strlcpy(dest->data, src->data, len + 1);
	dest->type = src->type;
	return (dest);
}

void	delete_node(t_ASTree *node)
{
	if (node)
		delete_node(node->left);
	else
		return ;
	delete_node(node->right);
	free(node->data);
	free(node);
}
