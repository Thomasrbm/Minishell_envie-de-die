/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:46:33 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 04:15:08 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*append_str(char *s, char *to_add)
{
	char	*tmp;

	tmp = ft_strjoin(s, to_add);
	free(s);
	return (tmp);
}

char	*append_char(char *s, char c)
{
	char	*tmp;
	int		len;

	len = ft_strlen(s);
	tmp = malloc(len + 2);
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, s, len + 1);
	tmp[len] = c;
	tmp[len + 1] = '\0';
	free(s);
	return (tmp);
}
