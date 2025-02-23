/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:48:48 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 23:50:13 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_quotes_state(char c, int *in_s, int *in_d)
{
	if (c == '\'' && !(*in_d))
		*in_s = !(*in_s);
	else if (c == '"' && !(*in_s))
		*in_d = !(*in_d);
}

// static void	copy_no_quotes(char *s, char *dest)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (s[i])
// 	{
// 		if ((s[i] == '\'' || s[i] == '"') && (i == 0 || s[i - 1] != '\\'))
// 		{
// 			update_quotes_state(s[i], &(int){0}, &(int){0});
// 			i++;
// 		}
// 		else
// 		{
// 			dest[j] = s[i];
// 			i++;
// 			j++;
// 		}
// 	}
// 	dest[j] = '\0';
// }

char	*remove_quotes(char *str)
{
	size_t	len;
	char	*result;

	if (!str || ft_strlen(str) < 2)
		return (ft_strdup(str));
	len = ft_strlen(str);
	if ((str[0] == '"' && str[len - 1] == '"')
		|| (str[0] == '\'' && str[len - 1] == '\''))
		result = ft_substr(str, 1, len - 2);
	else
		result = ft_strdup(str);
	return (result);
}
