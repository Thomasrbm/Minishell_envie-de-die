/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:40:46 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 00:41:11 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**dup_tokens(char **t, int start, int end)
{
	int		i;
	int		len;
	char	**new_t;

	len = 0;
	while (t[len])
		len++;
	if (end == -1)
		end = len - 1;
	if (start > end || start >= len || end >= len)
		return (NULL);
	new_t = malloc(sizeof(char *) * (end - start + 2));
	if (!new_t)
		return (NULL);
	i = start;
	while (i <= end)
	{
		new_t[i - start] = ft_strdup(t[i]);
		i++;
	}
	new_t[i - start] = NULL;
	return (new_t);
}

char	**ft_tabdup(char **tab)
{
	int		i;
	int		len;
	char	**new_tab;

	if (!tab)
		return (NULL);
	i = 0;
	len = 0;
	while (tab[len])
		len++;
	new_tab = malloc(sizeof(char *) * (len + 1));
	if (!new_tab)
		return (NULL);
	while (i < len)
	{
		new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}
