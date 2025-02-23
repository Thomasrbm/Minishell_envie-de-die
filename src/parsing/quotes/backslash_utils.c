/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:47:13 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 23:54:24 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_backslash(char *s, int pos)
{
	int	cnt;

	cnt = 0;
	pos--;
	while (pos >= 0 && s[pos] == '\\')
	{
		cnt++;
		pos--;
	}
	return (cnt);
}

void	handle_backslash(char *in, int *i, char **w)
{
	if (in[*i + 1] == '$' || in[*i + 1] == '"' || in[*i + 1] == '\\' || in[*i
			+ 1] == '\n')
	{
		(*i)++;
		if (in[*i])
		{
			*w = append_char(*w, in[*i]);
			(*i)++;
		}
	}
	else if (in[*i + 1] == '`')
		(*i)++;
	else
	{
		*w = append_char(*w, '\\');
		(*i)++;
	}
}

void	handle_singlequote(char *in, int *i, char **w)
{
	*w = append_char(*w, '\'');
	(*i)++;
	while (in[*i] && in[*i] != '\'')
	{
		*w = append_char(*w, in[*i]);
		(*i)++;
	}
	if (in[*i] == '\'')
	{
		*w = append_char(*w, '\'');
		(*i)++;
	}
}
