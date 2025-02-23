/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 01:16:46 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/23 08:34:11 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	quote(char *res, char *line, int *i, int *r)
{
	char	quote;

	quote = line[*i];
	res[(*r)++] = line[(*i)++];
	while (line[*i] && line[*i] != quote)
		res[(*r)++] = line[(*i)++];
	if (line[*i] == quote)
		res[(*r)++] = line[(*i)++];
}

int	mal_len(char **tab)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (tab[i])
	{
		total += calc_len_line(tab[i]);
		if (tab[i + 1])
			total++;
		i++;
	}
	return (total + 1);
}

void	append_delim(char *res, int *r, char *token, int token_len)
{
	int	k;

	if (*r > 0 && res[*r - 1] != ' ')
		res[(*r)++] = ' ';
	k = 0;
	while (k < token_len)
	{
		res[(*r)++] = token[k];
		k++;
	}
	res[(*r)++] = ' ';
}
