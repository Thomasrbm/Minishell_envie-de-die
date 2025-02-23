/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_preprocess2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 04:19:04 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 21:07:48 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	copy_no_marker(char *s, char *res)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == ESC_QUOTE && s[i + 1])
		{
			res[j++] = s[i + 1];
			i += 2;
		}
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
}

char	*remove_marker(char *s)
{
	char	*res;
	int		len;

	len = ft_strlen(s);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	copy_no_marker(s, res);
	return (res);
}
