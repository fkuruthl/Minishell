/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-command_level.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:28:36 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:33:45 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ASTree	*case_checker1(t_ASTree *rdrlist1, t_ASTree *rdrlist2,
		t_ASTree *smplcmdnode)
{
	t_ASTree	*result;
	t_ASTree	*save_rdr1;

	result = (t_ASTree *)malloc(sizeof(*result));
	if (!result)
		return (warn_message(), NULL);
	save_rdr1 = rdrlist1;
	set_node_type(result, NODE_RDRGEN);
	set_node_data(result, NULL);
	if (rdrlist1)
	{
		if (rdrlist2)
		{
			while (rdrlist1->left)
				rdrlist1 = rdrlist1->left;
			rdrlist1->left = rdrlist2;
			rdrlist1 = save_rdr1;
		}
		attach_branch(result, smplcmdnode, rdrlist1);
	}
	else
		return (free(result), smplcmdnode);
	return (result);
}

t_ASTree	*case_checker2(t_ASTree *rdrlist2, t_ASTree *smplcmdnode)
{
	t_ASTree	*result;

	result = (t_ASTree *)malloc(sizeof(*result));
	if (!result)
		return (warn_message(), NULL);
	if (rdrlist2)
	{
		set_node_type(result, NODE_RDRGEN);
		set_node_data(result, NULL);
		attach_branch(result, smplcmdnode, rdrlist2);
	}
	else
		return (free(result), smplcmdnode);
	return (result);
}

t_ASTree	*assign_rdrlist2(t_ASTree *smplcmdnode)
{
	t_ASTree	*rdrlist2;

	rdrlist2 = copy_node(smplcmdnode->right);
	delete_node(smplcmdnode->right);
	smplcmdnode->right = NULL;
	return (rdrlist2);
}
