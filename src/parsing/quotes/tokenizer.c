/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:48:23 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 07:07:12 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_tokens(char *in)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (in[i])
	{
		while (in[i] && ft_isspace(in[i]))
			i++;
		if (!in[i])
			break ;
		while (in[i] && !ft_isspace(in[i]))
			i++;
		cnt++;
	}
	return (cnt);
}

char	**ft_tokenize_line(char *in, t_shell *shell)
{
	char	**tokens;
	int		cnt;
	int		i;
	int		n;
	char	*word;

	in = parse_cmd(in);
	cnt = count_tokens(in);
	tokens = malloc(sizeof(char *) * (cnt + 1));
	if (!tokens)
		return (NULL);
	n = 0;
	i = 0;
	while (in[i])
	{
		while (in[i] && ft_isspace(in[i]))
			i++;
		if (!in[i])
			break ;
		word = ft_parse_word(in, &i, shell);
		tokens[n++] = word;
	}
	tokens[n] = NULL;
	free(in);
	return (tokens);
}
