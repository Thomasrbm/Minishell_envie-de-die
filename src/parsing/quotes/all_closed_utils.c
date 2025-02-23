/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_closed_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:16:31 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 19:16:31 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	process_single_quote(char *s, int *i, int *in_single)
{
	if (s[*i] == '\'')
	{
		*in_single = 0;
	}
	(*i)++;
	return (*i);
}

int	process_double_quote(char *s, int *i,
		int *in_double, int *backslashes)
{
	int	j;

	*backslashes = 0;
	j = *i - 1;
	while (j >= 0 && s[j] == '\\')
	{
		(*backslashes)++;
		j--;
	}
	if (s[*i] == '"' && (*backslashes % 2 == 0))
	{
		*in_double = 0;
	}
	(*i)++;
	return (*i);
}

int	process_normal(char *s, int *i, int *in_single, int *in_double)
{
	if (s[*i] == '\'')
	{
		*in_single = 1;
		(*i)++;
	}
	else if (s[*i] == '"')
	{
		*in_double = 1;
		(*i)++;
	}
	else if (s[*i] == '\\')
	{
		if (s[*i + 1] != '\0')
			*i += 2;
		else
			(*i)++;
	}
	else
	{
		(*i)++;
	}
	return (*i);
}
