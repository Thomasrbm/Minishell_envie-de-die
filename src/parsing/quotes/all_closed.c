/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_closed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:16:24 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 19:16:24 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	all_quotes_closed(char *s)
{
	int	i;
	int	in_single;
	int	in_double;
	int	backslashes;

	i = 0;
	in_single = 0;
	in_double = 0;
	backslashes = 0;
	while (s[i])
	{
		if (in_single)
			i = process_single_quote(s, &i, &in_single);
		else if (in_double)
			i = process_double_quote(s, &i, &in_double, &backslashes);
		else
			i = process_normal(s, &i, &in_single, &in_double);
	}
	return (!(in_single || in_double));
}
