/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:24:32 by throbert          #+#    #+#             */
/*   Updated: 2025/02/23 04:28:47 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/stat.h>

extern volatile __sig_atomic_t	g_signal;

/* Structures */

typedef struct s_wildcard
{
	int							s;
	int							p;
	int							star;
	int							match;
}								t_wildcard;

typedef struct t_shell
{
	int							exit_code;
	int							check;
	int							save_out;
	int							save_in;
	int							size;
	int							out_count;
	int							in_count;
	int							pipe_count;
	char						**env;
	char						**cmd;
}								t_shell;

typedef struct t_pipe
{
	int							pipefd[2];
	int							child_count;
	int							infile;
	int							outfile;
	pid_t						*wait_pid;
}								t_pipe;

typedef struct t_doc
{
	char						*str;
	char						*limiter;
}								t_doc;

# define ESC_QUOTE '\x1F'

/* Prototypes */

/* Signal management */
void							setup_signals(int mode);
void							setup_signals2(int mode);
int								wait_ignore(pid_t pid);
void							sig_handler(int signum);
void							sigint_handler_heredoc(int sig);

/* Readline */
char							*get_readline(t_shell *shell);

/* Builtins */
int								ft_pwd(void);
int								ft_env(t_shell *shell);
char							**edit_env_value(t_shell *shell, char *value,
									char *new_one);
t_shell							*ft_unset(t_shell *shell);
char							**get_unset_value(t_shell *shell);
t_shell							*ft_export(t_shell *shell);
t_shell							*ft_cd(t_shell *shell);
t_shell							*ft_echo(char **cmd, t_shell *shell);

/* Redirections */
void							redirect_child(t_shell *shell,
									int pipefd[2]);
void							redirect_loop(t_shell *shell);
int								count_pipe(char **cmd);
int								find_command_index(char **cmd);
int								is_delim_token(char *token);
char							**get_flag(t_shell *shell);
int								update_count(char *line, int *j, int *count,
									char *current);
int								check_line_delim_chain(char *line);
int								is_delim(char *s);
int								calc_len_line(char *line);
int								mal_len(char **tab);
void							append_delim(char *res, int *r, char *token,
									int token_len);
void							close_all(char *str, char *limiter,
									int pipe_fd[2], t_shell *shell);
int								process_cmd(t_shell *shell);
char							*find_env(char **env);
char							**split_path(char **cmd, char **env);
int								valid_cmd(char **cmd, char **env);
void							free_all(t_shell *shell, char **cmd_files);
void							exec_path(char **cmd, t_shell *shell);
void							binary_path(char **cmd, t_shell *shell);
int								process_redirect(t_shell *shell);
int								handle_doc(t_shell *shell, int i);
int								error_open(t_shell *shell, int i, int message);
int								open_file(t_shell *shell, int i, int check);
int								open_file_2(t_shell *shell, int i, int check);
int								redirect_output(t_shell *shell, int i);
int								is_last_input(t_shell *shell, int i);
int								redirect_input(t_shell *shell, int i);
int								redirect(t_shell *shell);

/* Error management */
void							error_message(char **cmd);
int								check_single_cmd(t_shell *shell);

/* More builtins */
int								is_redirection(t_shell *s);
t_shell							*is_builtin(t_shell *s);
long long						ft_exit(t_shell *shell);
long long						exit_limits(t_shell *shell, int i,
									long long status);
void							free_exit(t_shell *shell);
long long						ft_atol_safe(char *str, int *error);

/* Environment variables */
char							*get_env_value(char *var, t_shell shell);
char							*get_env(t_shell *shell, char *value);
/* edit_env_value already declared above */
char							**split_env_path(char **cmd, char **env);

/* AST */
int								exec_ast(t_shell *shell);
void							get_sigint(t_shell *shell);

/* Commands and execution */
int								check_first(char *argv, char **env);

/* Wildcards */
int								wildcard_match(char *pattern, char *str,
									t_wildcard *wc);
int								contains_wildcard(char *str);
t_list							*expand_arg_list(char **cmd, t_shell *shell);

/* Shell loop */
int								shell_loop(t_shell *shell);

/* Signal management (again) */
int								wait_ignore(pid_t pid);

/* Wildcards expansion */
char							**expand_wildcards(char **cmd, t_shell *shell);

/* Readline helper */
int								ft_isspace(char c);

/* Additional redirection functions */
void							quote(char *res, char *line, int *i, int *r);
void							append_delim(char *res, int *r, char *token,
									int token_len);
void							check_next_pipe(t_shell *shell);

char							**process_input_line(t_shell *shell);
int								is_redirect(char *cmd);
char							**next_pipe(char **cmd);
int								exec_builtin(char **cmd, t_shell *shell);
int								count_backslash(char *s, int pos);
int								err_semicolon(void);
int								err_ampersand(char *s);
int								err_curly(void);
char							*parse_cmd(char *line);
char							*ft_parse_word(char *in, int *pos,
									t_shell *shell);
char							*append_str(char *s, char *to_add);
char							*append_char(char *s, char c);
void							handle_doublequote(char *in, int *i, char **w,
									t_shell *shell);
void							handle_dollar(char *in, int *i, char **w,
									t_shell *shell);
void							handle_dollar_var(char *in, int *i, char **w,
									t_shell *shell);
void							handle_dollar_question(int *i, char **w,
									t_shell *shell);
void							handle_dollar_space(int *i, char **w);
void							handle_backslash(char *in, int *i, char **w);
void							handle_singlequote(char *in, int *i, char **w);
char							**ft_tokenize_line(char *in, t_shell *shell);
void							remove_markers(char **toks);
char							*remove_marker(char *s);
char							*preprocess_input(char *input);
int								is_only_backslashes_or_backtick(char *s);
int								check_error_token(char *s);
int								all_quotes_closed(char *s);
int								is_only_quotes(char *s);
int								find_split_pos(char **tokens, int *op_type);
char							**ft_tabdup(char **tab);
char							**dup_tokens(char **t, int start, int end);
int								local_exec(char **cmd, t_shell *shell);
int								path_exec(char **cmd, t_shell *shell, char *pv);
char							*ft_strjoin_free_both(char *s1, char *s2);
int								exec_cmd_external(char **cmd, t_shell *shell);
int								check_additional_cmd(char **cmd,
									t_shell *shell);
int								parse_expr(char **str, t_shell *shell);
int								validate_syntax(t_shell *shell, char *str);
char							*remove_quotes(char *s);
void							process_default_state(char *s, int idx[4]);
int								is_full_quoted(char *s);
int								err_backslash(void);
int								err_backtick(void);
void							process_inside_dq(char *s, int idx[3]);
char							*ft_parse_input(char *in, t_shell *shell);
int								validate_quotes(t_shell *shell, char *str);
int								fork_and_exec(t_shell *shell);

int								validate_cmd(char **cmd);
char							*ft_parse_input(char *in, t_shell *shell);

int								parse_state0(char *in, int *i,
									char **res, t_shell *shell);
int								parse_state1(char *in, int *i, char **res);
int								parse_state2(char *in, int *i, char **res,
									t_shell *shell);

void							process_single(int *i, int *in_single);
void							process_double_start(int *i, int *in_double);
void							process_backtick(int *i, int *in_backtick);
void							process_backslash(char *s, int *i);
void							process_double_in(char *s, int *i,
									int *in_double, int *in_backtick);

int								process_single_quote(char *s,
									int *i, int *in_single);
int								process_double_quote(char *s, int *i,
									int *in_double, int *backslashes);
int								process_normal(char *s, int *i,
									int *in_single, int *in_double);
char							*expand_variables_in_token(char *token,
									t_shell *shell);
t_list							*process_argument(char *arg);
t_list							*sort_list(t_list *lst);
int								is_directory(char *path);

// Ajouter avant handle_directory()
void 							process_directory(char *base_path, char *pattern,
									t_list **lst, int is_recursive);
char 							*ft_strjoin_free(char *s1, char *s2);
char 							*build_full_path(char *base, char *name);
int 							should_skip_entry(struct dirent *entry,
									int show_hidden);

char							*ft_process_replacement(char *str, char *old, size_t old_len,
										char *new, size_t new_len, char *result, size_t *i);
									
#endif
