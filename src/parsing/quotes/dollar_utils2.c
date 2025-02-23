/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 23:51:28 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 23:51:28 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	ft_count_occurrences(char *str, char *old)
{
	size_t	i;
	size_t	count;
	size_t	old_len;

	old_len = ft_strlen(old);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (ft_strncmp(&str[i], old, old_len) == 0)
		{
			count++;
			i += old_len - 1;
		}
		i++;
	}
	return (count);
}

char	*ft_allocate_result(size_t i, size_t count,
			size_t new_len, size_t old_len)
{
	return (malloc(i + count * (new_len - old_len) + 1));
}

char	*ft_strreplace(char *str, char *old, char *new)
{
	char	*result;
	size_t	old_len;
	size_t	new_len;
	size_t	i;
	size_t	count;

	old_len = ft_strlen(old);
	new_len = ft_strlen(new);
	count = ft_count_occurrences(str, old);
	i = 0;
	result = ft_allocate_result(i, count, new_len, old_len);
	if (!result)
		return (NULL);
	return (ft_process_replacement(str, old, old_len,
			new, new_len, result, &i));
}

char	*ft_process_replacement(char *str, char *old, size_t old_len,
	char *new, size_t new_len, char *result, size_t *i)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		if (ft_strncmp(str, old, old_len) == 0)
		{
			ft_memcpy(&result[*i], new, new_len);
			*i += new_len;
			str += old_len;
			count++;
		}
		else
			result[(*i)++] = *str++;
	}
	result[*i] = '\0';
	return (result);
}

char	*expand_variables_in_token(char *token, t_shell *shell)
{
	char	*expanded;
	int		pos;
	char	*result;

	pos = 0;
	expanded = ft_parse_word(token, &pos, shell);
	free(token);
	result = ft_strreplace(expanded, "//", "/");
	free(expanded);
	return (result);
}

void	handle_dollar(char *in, int *i, char **w, t_shell *shell)
{
	if (!in[*i + 1] || ft_isspace(in[*i + 1]))
		handle_dollar_space(i, w);
	else if (in[*i + 1] == '?')
		handle_dollar_question(i, w, shell);
	else
		handle_dollar_var(in, i, w, shell);
}
