/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:16:01 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 18:15:14 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	check_redir_end(char *cmd)
{
	int	i;

	if (!cmd)
		return (0);
	i = 0;
	while (cmd[i])
		i++;
	while (i > 0 && (cmd[i - 1] == ' ' || cmd[i - 1] == '\t'))
		i--;
	if (i > 0 && (cmd[i - 1] == '<' || cmd[i - 1] == '>' || cmd[i - 1] == '|'))
	{
		if (cmd[i - 1] == '<' || cmd[i - 1] == '>')
			write(2, "minishell: error near unexpected token\n", 40);
		else if (cmd[0] == '|' || cmd[i - 1] == '|')
			write(2, "Unclosed pipe\n", 14);
		rl_replace_line("", 0);
		rl_on_new_line();
		return (2);
	}
	return (0);
}

static char	*proc_redir(t_shell *shell, char *in, char *trim, int ret)
{
	if (ret == 2)
	{
		shell->exit_code = 2;
		add_history(in);
		free(trim);
		free(in);
		return (ft_strdup(""));
	}
	else if (ret)
	{
		free(trim);
		return (in);
	}
	return (NULL);
}

char	*get_readline(t_shell *shell)
{
	char	*in;
	char	*trim;
	int		ret;
	char	*res;

	in = readline("\033[1;32mminishell > \033[0m");
	if (!in)
		return (NULL);
	if (g_signal == SIGINT)
		get_sigint(shell);
	trim = ft_strtrim(in, " \t\n");
	if (!trim)
	{
		free(in);
		return (NULL);
	}
	ret = check_redir_end(trim);
	res = proc_redir(shell, in, trim, ret);
	if (res)
		return (res);
	if (*trim)
		add_history(in);
	free(trim);
	return (in);
}

void	get_sigint(t_shell *shell)
{
	shell->exit_code = 130;
	g_signal = 0;
}
