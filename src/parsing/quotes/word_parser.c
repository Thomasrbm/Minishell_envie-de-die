/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:48:09 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 18:10:21 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*parse_tilde(char *in, int *i, char *w, t_shell *shell)
{
	char	*tmp;
	char	*home;

	if (!in[*i + 1] || in[*i + 1] == '/' || ft_isspace(in[*i + 1]))
	{
		home = get_env_value("HOME", *shell);
		if (!home)
			home = getenv("HOME");
		if (!home)
			w = append_char(w, '~');
		else
		{
			tmp = ft_strdup(home);
			w = append_str(w, tmp);
			free(tmp);
		}
	}
	else
		w = append_char(w, '~');
	(*i)++;
	return (w);
}

/* On appelle remove_quotes juste après la construction */
char	*ft_parse_word(char *in, int *pos, t_shell *shell)
{
	char	*w;
	int		i;

	w = ft_strdup("");
	i = *pos;
	while (in[i] && !ft_isspace(in[i]))
	{
		if (in[i] == '\\')
			handle_backslash(in, &i, &w);
		else if (in[i] == '\'')
			handle_singlequote(in, &i, &w);
		else if (in[i] == '"')
			handle_doublequote(in, &i, &w, shell);
		else if (in[i] == '~' && !ft_strlen(w))
			w = parse_tilde(in, &i, w, shell);
		else if (in[i] == '$')
			handle_dollar(in, &i, &w, shell);
		else
		{
			w = append_char(w, in[i]);
			i++;
		}
	}
	*pos = i;
	return (w);
}
