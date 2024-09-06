/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsalah <hsalah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:53:48 by hsalah            #+#    #+#             */
/*   Updated: 2024/08/02 09:13:40 by hsalah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_value(char **env_list, char *str)
{
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	if (!env_list || !str)
		return (NULL);
	while (env_list[i])
	{
		if (bool_key_match(env_list[i], str))
			break ;
		i++;
	}
	if (!env_list[i])
		return (NULL);
	j = 0;
	while (env_list[i][j] && env_list[i][j] != '=')
		j++;
	if (!env_list[i][j])
		return (NULL);
	buffer = ft_strdup(env_list[i] + j + 1);
	if (!buffer)
		warn_message();
	return (buffer);
}

char	*go_to_home(t_minishell *shell, char *str)
{
	char	*new_dir;
	int		i;
	int		j;
	char	*home_path;
	int		len;

	home_path = get_value(shell->env, "HOME");
	if (!home_path)
		return (ft_dprintf(2, "-minishell: cd: HOME not set\n"), NULL);
	len = ft_strlen(home_path) + (ft_strlen(str) - 1);
	new_dir = (char *)malloc(len + 1);
	ft_strlcpy(new_dir, home_path, ft_strlen(home_path) + 1);
	j = ft_strlen(home_path);
	i = 1;
	while (str[i])
		new_dir[j++] = str[i++];
	new_dir[j] = '\0';
	return (free(home_path), new_dir);
}

char	*go_to_oldpwd(t_minishell *shell)
{
	char	*new_dir;
	char	*oldpwd_path;

	oldpwd_path = get_value(shell->env, "OLDPWD");
	if (!oldpwd_path)
		return (ft_dprintf(2, "-minishell: cd: OLDPWD not set\n"), NULL);
	new_dir = ft_strdup(oldpwd_path);
	ft_dprintf(1, "%s\n", new_dir);
	return (free(oldpwd_path), new_dir);
}

char	*assign_new_dir(t_minishell *shell, t_command *cmd)
{
	char	*home_path;
	char	*new_dir;
	int		arg_count;

	new_dir = NULL;
	arg_count = count_cd_args(cmd);
	if (arg_count > 1)
		return (ft_dprintf(2, "-minishell: cd: too many arguments\n"), NULL);
	if (arg_count == 0 || (arg_count == 1 && !(cmd->cmd_args[1][0])))
	{
		home_path = get_value(shell->env, "HOME");
		if (!home_path)
			return (ft_dprintf(2, "-minishell: cd: HOME not set\n"), NULL);
		new_dir = home_path;
	}
	else if (arg_count == 1 && cmd->cmd_args[1][0])
	{
		if (!ft_strncmp(cmd->cmd_args[1], "-", 2))
			new_dir = go_to_oldpwd(shell);
		else if (!ft_strncmp(cmd->cmd_args[1], "~", 1))
			new_dir = go_to_home(shell, cmd->cmd_args[1]);
		else
			new_dir = ft_strdup(cmd->cmd_args[1]);
	}
	return (new_dir);
}

int	ft_cd(t_minishell *shell, t_command *cmd)
{
	char	*current_dir;
	char	*new_dir;

	shell->exit_status = 0;
	current_dir = getcwd(NULL, 0);
	if (!cmd->cmd_args)
		return (free(current_dir), 1);
	new_dir = assign_new_dir(shell, cmd);
	if (new_dir)
	{
		if (chdir(new_dir) == -1)
			return (shell->exit_status = 1,
				ft_dprintf(2, "-minishell: cd: %s: No such file or directory\n",
					new_dir), free(new_dir), free(current_dir), 1);
		shell->env = update_env_list(shell->env, "OLDPWD", current_dir);
		free(current_dir);
		current_dir = getcwd(NULL, 0);
		shell->env = update_env_list(shell->env, "PWD", current_dir);
	}
	else
		shell->exit_status = 1;
	return (free(current_dir), free(new_dir), 0);
}
