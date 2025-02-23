/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 01:54:43 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/22 21:01:46 by rbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_pipe(char	**cmd)
{
	int	pipe_count;
	int	i;

	i = 0;
	pipe_count = 0;
	while (cmd[i] != NULL)
	{
		if (!ft_strcmp(cmd[i], "|"))
			pipe_count++;
		i++;
	}
	return (pipe_count);
}

int	is_redirect(char *cmd)
{
	if (!ft_strcmp(cmd, "<") || !ft_strcmp(cmd, ">")
		|| !ft_strcmp(cmd, ">>") || !ft_strcmp(cmd, "<<"))
	{
		return (1);
	}
	return (0);
}
