/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:52:11 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 17:10:27 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_backslash_tick(t_shell *shell, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\\' && !s[i + 1])
		{
			err_backslash();
			shell->exit_code = 2;
			return (1);
		}
		if (s[i] == '`' && !ft_strchr(s + i + 1, '`'))
		{
			err_backtick();
			shell->exit_code = 2;
			return (1);
		}
		i++;
	}
	return (0);
}

int	validate_basic(t_shell *shell, char *str)
{
	if (is_only_backslashes_or_backtick(str))
	{
		free(str);
		return (1);
	}
	if (check_error_token(str))
	{
		free(str);
		shell->exit_code = 2;
		return (1);
	}
	return (0);
}

int	validate_quotes(t_shell *shell, char *str)
{
	if (!all_quotes_closed(str))
	{
		ft_putstr_fd("Unclosed quotes\n", 2);
		shell->exit_code = 2;
		return (1);
	}
	if (is_only_quotes(str))
	{
		ft_putstr_fd("Command '' not found\n", 2);
		shell->exit_code = 127;
		return (1);
	}
	return (0);
}

int	validate_syntax(t_shell *shell, char *str)
{
	if (check_backslash_tick(shell, str))
		return (1);
	if (validate_basic(shell, str))
		return (1);
	if (validate_quotes(shell, str))
		return (1);
	return (0);
}
