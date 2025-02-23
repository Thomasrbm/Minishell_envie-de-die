/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_state_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:44:11 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 07:08:55 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	process_inside_dq(char *s, int idx[3])
{
	if (s[idx[0]] == '"' && (count_backslash(s, idx[0]) % 2 == 0))
		idx[1] = 0;
	else if (s[idx[0]] == '`' && (count_backslash(s, idx[0]) % 2 == 0))
		idx[2] = !idx[2];
	else if (s[idx[0]] == '\\' && s[idx[0] + 1] == '`')
		idx[0]++;
	idx[0]++;
}

void	process_default_state(char *s, int idx[4])
{
	if (s[idx[0]] == '\'')
		idx[1] = 1;
	else if (s[idx[0]] == '"')
		idx[2] = 1;
	else if (s[idx[0]] == '`')
		idx[3] = !idx[3];
	else if (s[idx[0]] == '\\' && s[idx[0] + 1])
		idx[0]++;
	idx[0]++;
}
