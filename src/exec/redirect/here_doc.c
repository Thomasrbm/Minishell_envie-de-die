/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:50:47 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/23 16:26:06 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// close every fd and free all char * if STDIN is close or EOF is
// encountered.
void	close_all(char *str, char *limiter, int pipe_fd[2], t_shell *shell)
{
	close(shell->save_out);
	close(shell->save_in);
	if (str)
		free(str);
	if (limiter)
		free(limiter);
	get_next_line(-1);
	close(pipe_fd[1]);
}

// here_doc loop that play until the LIMITER is typed in the terminal
static void	handle_flex(t_doc *doc)
{
	char	*flex;

	flex = ft_strdup(doc->limiter);
	flex[ft_strlen(flex) - 1] = '\0';
	ft_putstr_fd(flex, 2);
	free(flex);
}

static void	handle_doc_error(t_shell *shell, t_doc *doc,
		int pipefd[2])
{
	if (g_signal == SIGINT)
	{
		close_all(doc->str, doc->limiter, pipefd, shell);
		free(doc);
		free_all(shell, NULL);
		exit(130);
	}
	if (doc->str == NULL)
	{
		ft_putstr_fd("Minishell: warning: here_document", 2);
		ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
		handle_flex(doc);
		ft_putstr_fd("')\n", 2);
		close_all(doc->str, doc->limiter, pipefd, shell);
		free(doc);
		free_all(shell, NULL);
		exit(EXIT_SUCCESS);
	}
	if (ft_strncmp(doc->str, doc->limiter, ft_strlen(doc->str)) == 0)
	{
		close_all(doc->str, doc->limiter, pipefd, shell);
		free(doc);
		free_all(shell, NULL);
		exit(EXIT_SUCCESS);
	}
}

// here_doc loop that play until the LIMITER is typed in the terminal
void	here_doc(t_shell *shell, int i, int pipefd[2])
{
	t_doc	*doc;

	doc = malloc(sizeof(t_doc));
	close(pipefd[0]);
	setup_signals2(2);
	doc->limiter = ft_strjoin(shell->cmd[i + 1], "\n");
	while (1)
	{
		doc->str = get_next_line(0);
		handle_doc_error(shell, doc, pipefd);
		if (is_last_input(shell, i) == 0)
			ft_putstr_fd(doc->str, pipefd[1]);
		free(doc->str);
	}
	return ;
}

int	handle_doc(t_shell *shell, int i)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		here_doc(shell, i, pipefd);
	else
	{
		close(pipefd[1]);
		if (is_last_input(shell, i) == 0)
			dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	return (wait_ignore(pid));
}
