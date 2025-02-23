/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:18:54 by throbert          #+#    #+#             */
/*   Updated: 2025/02/21 14:40:22 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_n_flag(char *s)
{
	int	i;

	if (!s || s[0] != '-')
		return (0);
	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	echo_loop(char **cmd, int i)
{
	while (cmd[i])
	{
		ft_printf("%s", cmd[i]);
		if (cmd[i + 1])
			ft_printf(" ");
		i++;
	}
}

t_shell	*ft_echo(char **cmd, t_shell *shell)
{
	int	no_newline;
	int	i;

	no_newline = 0;
	i = 1;
	shell->exit_code = 0;
	while (cmd[i] && is_valid_n_flag(cmd[i]))
	{
		no_newline = 1;
		i++;
	}
	echo_loop(cmd, i);
	if (!no_newline)
		ft_printf("\n");
	return (shell);
}
