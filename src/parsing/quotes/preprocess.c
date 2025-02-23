/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 06:29:32 by throbert          #+#    #+#             */
/*   Updated: 2025/02/24 00:32:43 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	process_paren(char *in, char *res, int *i, int *j)
{
	if (in[*i] == '(' || in[*i] == ')')
	{
		if (*j > 0 && res[*j - 1] != ' ')
			res[(*j)++] = ' ';
		res[(*j)++] = in[(*i)++];
		if (in[*i] != ' ' && in[*i] != '\0')
			res[(*j)++] = ' ';
		return (1);
	}
	return (0);
}

static int	process_double_op(char *in, char *res, int *i, int *j)
{
	if (in[*i] == '&' && in[*i + 1] == '&')
	{
		if (*j > 0 && res[*j - 1] != ' ')
			res[(*j)++] = ' ';
		res[(*j)++] = '&';
		res[(*j)++] = '&';
		*i += 2;
		if (in[*i] && !ft_isspace(in[*i]))
			res[(*j)++] = ' ';
		return (1);
	}
	if (in[*i] == '|' && in[*i + 1] == '|')
	{
		if (*j > 0 && res[*j - 1] != ' ')
			res[(*j)++] = ' ';
		res[(*j)++] = '|';
		res[(*j)++] = '|';
		*i += 2;
		if (in[*i] && !ft_isspace(in[*i]))
			res[(*j)++] = ' ';
		return (1);
	}
	return (0);
}

static int	process_non_quote(char *in, char *res, int *i, int *j)
{
	if (process_paren(in, res, i, j))
		return (1);
	if (process_double_op(in, res, i, j))
		return (1);
	return (0);
}

static void	preprocess_loop(char *in, char *res, int idx[3])
{
	while (in[idx[0]])
	{
		if (!idx[2] && process_non_quote(in, res, &idx[0], &idx[1]))
			continue ;
		if (in[idx[0]] == '"' || in[idx[0]] == '\'')
		{
			idx[2] = !idx[2];
			res[idx[1]++] = in[idx[0]++];
		}
		if (in[idx[0]] != '"' && in[idx[0]] != '\'')
			res[idx[1]++] = in[idx[0]++];
	}
}

char	*preprocess_input(char *in)
{
	int		len;
	int		idx[3];
	char	*res;

	len = ft_strlen(in);
	res = malloc(len * 2 + 1);
	if (!res)
		return (NULL);
	idx[0] = 0;
	idx[1] = 0;
	idx[2] = 0;
	preprocess_loop(in, res, idx);
	res[idx[1]] = '\0';
	return (res);
}
