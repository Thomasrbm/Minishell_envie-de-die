/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 00:35:59 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 16:21:49 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	validate_cmd_initial(char **cmd)
{
	if (!cmd || !cmd[0])
		return (1);
	if (!ft_strcmp(cmd[0], "/"))
	{
		error_message(cmd);
		free_tab(cmd);
		return (127);
	}
	if (!ft_strcmp(cmd[0], ".") || !ft_strcmp(cmd[0], ".."))
	{
		error_message(cmd);
		return (127);
	}
	return (0);
}

int	validate_cmd(char **cmd)
{
	int		ret;
	char	*trim;

	ret = validate_cmd_initial(cmd);
	if (ret)
		return (ret);
	trim = ft_strtrim(cmd[0], " \t\n");
	if (ft_strcmp(cmd[0], trim))
	{
		error_message(cmd);
		free(trim);
		free_tab(cmd);
		return (127);
	}
	free(trim);
	return (0);
}

int	check_additional_cmd(char **cmd, t_shell *shell)
{
	if (cmd[1]
		&& !ft_strchr(cmd[0], '/')
		&& check_first(cmd[0], shell->env))
	{
		error_message(cmd);
		shell->exit_code = 127;
		free_tab(cmd);
		return (127);
	}
	return (0);
}
