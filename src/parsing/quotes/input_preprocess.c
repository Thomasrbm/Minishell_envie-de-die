/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_preprocess.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:52:05 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 18:12:09 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*read_and_trim(t_shell *shell)
{
	char	*in;
	char	*trim;

	in = get_readline(shell);
	if (!in)
	{
		ft_putstr_fd("exit\n", 2);
		return (NULL);
	}
	trim = ft_strtrim(in, " \n\t");
	free(in);
	if (!trim)
		return (NULL);
	if (!*trim)
		trim[0] = '\0';
	return (trim);
}

void	remove_markers(char **toks)
{
	int		i;
	char	*tmp;

	i = 0;
	while (toks && toks[i])
	{
		tmp = remove_marker(toks[i]);
		free(toks[i]);
		toks[i] = tmp;
		i++;
	}
}

char	**process_input_line(t_shell *shell)
{
	char	*original_trim;
	char	*parsed_trim;
	char	**toks;

	original_trim = read_and_trim(shell);
	if (!original_trim)
		return (NULL);
	parsed_trim = ft_parse_input(original_trim, shell);
	free(original_trim);
	if (!parsed_trim)
		return (NULL);
	toks = ft_tokenize_line(parsed_trim, shell);
	remove_markers(toks);
	free(parsed_trim);
	return (toks);
}
