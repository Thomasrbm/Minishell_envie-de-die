/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:34:46 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 18:12:30 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fork_and_exec(t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("fork", 2);
		return (127);
	}
	if (pid == 0)
	{
		setup_signals(0);
		status = exec_cmd_external(shell->cmd, shell);
		exit(status);
	}
	return (wait_ignore(pid));
}

int	exec_ast_cmd_node(t_shell *shell)
{
	int	ret;

	ret = validate_cmd(shell->cmd);
	if (ret)
		return (ret);
	if (is_redirection(shell) == 0)
		return (redirect(shell));
	if (is_builtin(shell)->check == 0)
		return (exec_builtin(shell->cmd, shell));
	if (check_single_cmd(shell))
		return (shell->exit_code);
	ret = check_additional_cmd(shell->cmd, shell);
	if (ret)
		return (ret);
	return (fork_and_exec(shell));
}

int	exec_ast(t_shell *shell)
{
	int	status;

	if (is_redirection(shell) == 0)
		status = redirect(shell);
	else if (is_builtin(shell)->check == 0)
		status = exec_builtin(shell->cmd, shell);
	else
		status = exec_cmd_external(shell->cmd, shell);
	return (status);
}
