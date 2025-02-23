/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:36:29 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 06:26:38 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_first(char *argv, char **env)
{
	char	**cmd;
	char	**files;
	int		i;

	cmd = ft_split(argv, ' ');
	if (!cmd || !cmd[0])
		return (1);
	files = split_env_path(cmd, env);
	i = 0;
	if (files)
	{
		while (files[i])
		{
			if (access(files[i], X_OK) == 0)
			{
				free_tab(cmd);
				free_tab(files);
				return (0);
			}
			i++;
		}
	}
	free_tab(cmd);
	free_tab(files);
	return (1);
}

int	exec_cmd_external(char **cmd, t_shell *shell)
{
	char	*pv;

	if (!cmd || !cmd[0])
		return (127);
	if (ft_strchr(cmd[0], '/'))
		return (local_exec(cmd, shell));
	if (check_first(cmd[0], shell->env) != 0)
	{
		error_message(cmd);
		shell->exit_code = 127;
		return (127);
	}
	pv = get_env_value("PATH", *shell);
	if (!pv || !pv[0])
	{
		error_message(cmd);
		shell->exit_code = 127;
		if (pv)
			free(pv);
		return (127);
	}
	return (path_exec(cmd, shell, pv));
}

int	check_single_cmd(t_shell *shell)
{
	if (shell->cmd && shell->cmd[0] && !shell->cmd[1])
	{
		if (ft_strchr(shell->cmd[0], '/'))
		{
			if (access(shell->cmd[0], X_OK) != 0)
			{
				error_message(shell->cmd);
				shell->exit_code = 127;
				shell->cmd = free_tab(shell->cmd);
				return (1);
			}
		}
		else if (check_first(shell->cmd[0], shell->env))
		{
			error_message(shell->cmd);
			shell->exit_code = 127;
			shell->cmd = free_tab(shell->cmd);
			return (1);
		}
	}
	return (0);
}
