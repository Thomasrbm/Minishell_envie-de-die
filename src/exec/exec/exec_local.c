/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_local.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:37:31 by throbert          #+#    #+#             */
/*   Updated: 2025/02/24 00:02:21 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}

int	local_exec(char **cmd, t_shell *shell)
{
	if (access(cmd[0], X_OK) == 0)
		execve(cmd[0], cmd, shell->env);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": Is a directory\n", 2);
	free_tab(shell->cmd);
	free_tab(cmd);
	free_tab(shell->env);
	free(shell);
	return (127);
}

int	path_exec2(char **cmd, char **ps, t_shell *shell, int j)
{
	char	*fp;

	fp = ft_strjoin(ps[j], "/");
	if (!fp)
		return (127);
	fp = ft_strjoin_free_both(fp, ft_strdup(cmd[0]));
	if (fp && access(fp, X_OK) == 0)
	{
		execve(fp, cmd, shell->env);
		free(fp);
		free_tab(ps);
		error_message(cmd);
		error_message(cmd);
		shell->exit_code = 127;
		exit(127);
	}
	free(fp);
	return (-1);
}

int	try_paths(char **ps, char **cmd, t_shell *shell)
{
	int	j;
	int	ret;

	j = 0;
	while (ps[j])
	{
		ret = path_exec2(cmd, ps, shell, j);
		if (ret != -1)
			return (ret);
		j++;
	}
	return (-1);
}

int	path_exec(char **cmd, t_shell *shell, char *pv)
{
	char	**ps;
	int		ret;

	ps = ft_split(pv, ':');
	free(pv);
	if (!ps)
	{
		error_message(cmd);
		shell->exit_code = 127;
		return (127);
	}
	ret = try_paths(ps, cmd, shell);
	free_tab(ps);
	if (ret != -1)
		return (ret);
	error_message(cmd);
	shell->exit_code = 127;
	return (127);
}
