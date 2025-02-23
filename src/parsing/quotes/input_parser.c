/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:51:58 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 18:56:05 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	parse_state0(char *in, int *i, char **res, t_shell *shell)
{
	int	idx[4];

	idx[0] = *i;
	idx[1] = 0;
	idx[2] = 0;
	idx[3] = 0;
	process_default_state(in, idx);
	*i = idx[0];
	if (!in[*i])
		return (0);
	if (in[*i] == '\'')
		return (1);
	if (in[*i] == '"')
		return (2);
	if (in[*i] == '$')
	{
		handle_dollar(in, i, res, shell);
		return (0);
	}
	*res = append_char(*res, in[*i]);
	return (0);
}

int	parse_state1(char *in, int *i, char **res)
{
	if (in[*i] == '\'')
		return (0);
	*res = append_char(*res, in[*i]);
	return (1);
}

void	handle_state2_dollar(char *in, int *i, char **res, t_shell *shell)
{
	char	*tmp;
	char	*var;
	int		start;

	if (in[*i + 1] == '?')
	{
		tmp = ft_itoa(shell->exit_code);
		*res = append_str(*res, tmp);
		free(tmp);
		(*i)++;
	}
	else
	{
		start = *i + 1;
		while (in[*i + 1] && (ft_isalnum(in[*i + 1]) || in[*i + 1] == '_'))
			(*i)++;
		tmp = ft_substr(in, start, *i - start + 1);
		var = get_env_value(tmp, *shell);
		free(tmp);
		*res = append_str(*res, var);
		free(var);
	}
}

int	handle_state2_backslash(char *in, int *i, char **res)
{
	char	next_char;

	next_char = in[*i + 1];
	if (next_char == '$' || next_char == '`' || next_char == '"'
		|| next_char == '\\' || next_char == '\n')
	{
		(*i)++;
		*res = append_char(*res, next_char);
	}
	else
		*res = append_char(*res, '\\');
	(*i)++;
	return (2);
}

int	parse_state2(char *in, int *i, char **res, t_shell *shell)
{
	if (in[*i] == '"')
		return (0);
	if (in[*i] == '\\')
		return (handle_state2_backslash(in, i, res));
	else if (in[*i] == '$')
	{
		handle_state2_dollar(in, i, res, shell);
		return (2);
	}
	else
	{
		*res = append_char(*res, in[*i]);
		(*i)++;
		return (2);
	}
}
