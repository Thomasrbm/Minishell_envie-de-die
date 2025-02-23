/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:40:15 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 04:53:51 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	parse_factor(char **str, t_shell *shell)
{
	char	**arr;
	int		i;

	(void)shell;
	i = 0;
	while (**str == ' ')
		(*str)++;
	if (**str == '(')
	{
		(*str)++;
		(void)parse_expr(str, shell);
		if (**str == ')')
			(*str)++;
		return (0);
	}
	arr = ft_split(*str, ' ');
	while ((*str)[i] && (*str)[i] != ' ' && (*str)[i] != ')')
		i++;
	(*str) += i;
	free_tab(arr);
	return (0);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	parse_expr(char **str, t_shell *shell)
{
	int	ret;

	ret = parse_factor(str, shell);
	while (**str && **str != ')')
	{
		while (**str == ' ')
			(*str)++;
		if (!**str || **str == ')')
			break ;
		if (((*str)[0] == '&' && (*str)[1] == '&') ||
			((*str)[0] == '|' && (*str)[1] == '|'))
			(*str) += 2;
		ret = parse_factor(str, shell);
	}
	return (ret);
}
