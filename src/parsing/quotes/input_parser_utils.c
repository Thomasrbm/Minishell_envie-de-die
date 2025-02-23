/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:23:29 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 18:23:29 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_parse_input(char *in, t_shell *shell)
{
	if (validate_syntax(shell, in))
		return (ft_strdup(""));
	return (parse_cmd(in));
}

char	*ft_parser_main(char *in, t_shell *shell)
{
	char	*res;
	int		state;
	int		i;

	res = ft_strdup("");
	state = 0;
	i = 0;
	while (in[i])
	{
		if (state == 0)
			state = parse_state0(in, &i, &res, shell);
		else if (state == 1)
			state = parse_state1(in, &i, &res);
		else if (state == 2)
			state = parse_state2(in, &i, &res, shell);
		if (in[i])
			i++;
	}
	if (state != 0)
	{
		free(res);
		return (ft_strdup(""));
	}
	return (res);
}
