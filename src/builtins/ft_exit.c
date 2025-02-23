/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 22:55:53 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/23 16:20:05 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// exit error message in case the exit code contain a non numeric
// argument.
static void	exit_error_message(t_shell *shell)
{
	ft_putstr_fd("Minishell: exit: ", 2);
	ft_putstr_fd(shell->cmd[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_exit(shell);
	exit(2);
}

void	free_exit(t_shell *shell)
{
	if (shell->cmd)
		free_tab(shell->cmd);
	if (shell->env)
		free_tab(shell->env);
	free(shell);
}

// process the verification if the exit value is valid or no

long long	exit_limits(t_shell *shell, int i, long long status)
{
	if (shell->cmd[1][0] == '-')
		i = 1;
	if (shell->cmd[1][0] == '-' && shell->cmd[1][1] == '\0')
		exit_error_message(shell);
	while (shell->cmd[1][i])
	{
		if (!ft_isdigit(shell->cmd[1][i]))
			exit_error_message(shell);
		i++;
	}
	return (status);
}

long long	ft_exit(t_shell *shell)
{
	long long	status;
	int			error;
	int			i;

	i = 0;
	ft_putstr_fd("exit\n", 2);
	if (tab_size(shell->cmd) > 2)
	{
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (!shell->cmd[1])
	{
		status = shell->exit_code;
		free_exit(shell);
		exit(status);
	}
	status = ft_atol_safe(shell->cmd[1], &error);
	if (error)
		exit_error_message(shell);
	status = exit_limits(shell, i, status);
	free_exit(shell);
	exit(status);
}
