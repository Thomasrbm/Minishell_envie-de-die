/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:33:19 by throbert          #+#    #+#             */
/*   Updated: 2025/02/24 00:27:58 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* 
 * Duplicates a linked list by copying the content of each node.
 */
t_list	*duplicate_list(t_list *orig)
{
	t_list	*new = NULL;
	t_list	*tmp = orig;

	while (tmp)
	{
		ft_lstadd_back(&new, ft_lstnew(ft_strdup(tmp->content)));
		tmp = tmp->next;
	}
	return new;
}

/* 
 * Checks if the token is a redirection operator (>, >>, <, <<).
 */
static int	is_redirection_operator(char *token)
{
	return (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0
		|| ft_strcmp(token, "<") == 0 || ft_strcmp(token, "<<") == 0);
}

/* 
 * Converts a linked list into an array of strings.
 */
char	**lst_to_tab(t_list *lst)
{
	int		size;
	char	**tab;
	int		i;
	t_list	*tmp;

	size = ft_lstsize(lst);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	i = 0;
	tmp = lst;
	while (tmp)
	{
		tab[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

/* Processes a directory to expand a wildcard pattern */
void process_directory(char *base_path, char *pattern, t_list **lst, int is_recursive)
{
	DIR *dir = opendir(base_path);
	struct dirent *entry;
	char *wild_part;
	int show_hidden;
	int expect_directory;
	char *last_slash;
	char *pattern_copy = ft_strdup(pattern);

	(void)is_recursive;
	if (!dir)
	{
		free(pattern_copy);
		return;
	}

	if (strcmp(base_path, "/") == 0 && pattern_copy[0] == '/')
		pattern_copy++;

	last_slash = strrchr(pattern_copy, '/');
	if (last_slash)
	{
		*last_slash = '\0'; 
		wild_part = last_slash + 1;
		char *new_base = build_full_path(base_path, pattern_copy);
		char *tmp = ft_strdup(wild_part);
		pattern = tmp;
		base_path = new_base;
	}
	else
	{
		wild_part = pattern_copy;
	}

	show_hidden = (wild_part[0] == '.' || strstr(pattern_copy, "/."));
	expect_directory = (pattern_copy[strlen(pattern_copy) - 1] == '/');

	entry = readdir(dir);
	while (entry)
	{
		char *full_path;
		struct stat st;
		char *entry_name;

		if (should_skip_entry(entry, show_hidden))
		{
			entry = readdir(dir);
		}
		else
		{
			full_path = build_full_path(base_path, entry->d_name);
			if (stat(full_path, &st) == -1)
			{
				free(full_path);
				entry = readdir(dir);
			}
			else
			{
				entry_name = ft_strdup(full_path);
				free(full_path);

				if (!entry_name)
				{
					entry = readdir(dir);
				}
				else
				{
					if (S_ISDIR(st.st_mode)) 
					{
						if (expect_directory && wildcard_match(wild_part, entry->d_name, NULL))
						{
							char *dir_name = ft_strjoin(entry_name, "/");
							ft_lstadd_back(lst, ft_lstnew(dir_name));
							free(entry_name);
						}
						else if (wildcard_match(wild_part, entry->d_name, NULL))
						{
							ft_lstadd_back(lst, ft_lstnew(entry_name));
						}
						else
						{
							free(entry_name);
						}
					}
					else if (wildcard_match(wild_part, entry->d_name, NULL))
					{
						ft_lstadd_back(lst, ft_lstnew(entry_name));
					}
					else
					{
						free(entry_name);
					}
					entry = readdir(dir);
				}
			}
		}
	}

	closedir(dir);
	free(pattern_copy);
	if (last_slash)
		free(base_path);
}

static void handle_multilevel_pattern(char *pattern, t_list **results)
{
    char *saveptr;
    char *path = strtok_r(pattern, "/", &saveptr);
    char *subpattern = strtok_r(NULL, "\0", &saveptr);
    int is_absolute = 0;
    if (pattern[0] == '/') {
        is_absolute = 1;
    }
    char *root_path;
    if (is_absolute == 1) {
        root_path = ft_strdup("/");
    } else {
        root_path = ft_strdup(".");
    }

    if (!path || !subpattern) {
        free(root_path);
        return;
    }

    t_list *dirs = NULL;
    if (is_absolute == 1) {
        process_directory(root_path, path, &dirs, 0);
    } else {
        dirs = expand_arg_list((char*[]){path, NULL}, NULL);
    }

    if (dirs != NULL) {
        while (dirs)
        {
            if (dirs->content && is_directory((char *)dirs->content)) {
                char *full_pattern = ft_strjoin((char *)dirs->content, "/");
                full_pattern = ft_strjoin_free(full_pattern, subpattern);
                process_directory((char *)dirs->content, full_pattern, results, 0);
                free(full_pattern);
            }
            dirs = dirs->next;
        }
    }

    ft_lstclear(&dirs, free);
    free(root_path);
}



t_list	*sort_list(t_list *lst)
{
	t_list	*i;
	t_list	*j;
	void	*tmp;

	i = lst;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (strcmp(i->content, j->content) > 0)
			{
				tmp = i->content;
				i->content = j->content;
				j->content = tmp;
			}
			j = j->next;
		}
		i = i->next;
	}
	return (lst);
}

t_list *expand_arg_list(char **cmd, t_shell *shell)
{
	t_list *results = NULL;
	(void)shell;

	int i = 0;
	while (cmd[i])
	{
		char *pattern = ft_strdup(cmd[i]);
		if (strchr(pattern, '/')) {
			if (pattern[0] == '/') {
				process_directory("/", pattern + 1, &results, 0);
				free(pattern); // Ajouter cette ligne
			} else {
				handle_multilevel_pattern(pattern, &results);
				free(pattern); // Ajouter cette ligne
			}
		} else {
			process_directory(".", pattern, &results, 0);
			free(pattern); // Ajouter cette ligne
		}
		i++;
	}
	return sort_list(results);
}

/* 
 * Processes the given argument by removing quotes and expanding wildcards if needed.
 */
t_list	*process_argument(char *arg)
{
	t_list	*lst;
	char	*processed_arg;
	int		was_quoted;
	size_t	len;

	len = ft_strlen(arg);
	was_quoted = 0;

	if ((len >= 2) && 
		((arg[0] == '"' && arg[len - 1] == '"') || 
		(arg[0] == '\'' && arg[len - 1] == '\''))) 
	{
		was_quoted = 1;
		processed_arg = remove_quotes(arg); 
	}
	else 
	{
		processed_arg = ft_strdup(arg);
	}

	if (!was_quoted && contains_wildcard(processed_arg)) 
	{
		lst = expand_arg_list((char*[]){processed_arg, NULL}, NULL);
		free(processed_arg);
		if (lst) {
			t_list *copy = duplicate_list(lst); 
			ft_lstclear(&lst, free);
			return copy;
		}
		return ft_lstnew(ft_strdup(arg));
	}
	else 
	{
		lst = ft_lstnew(processed_arg);
	}
	return lst;
}

/* 
 * Expands wildcards in a list of commands and handles redirection operators.
 */
t_list	*expand_wildcards_list(char **cmd, t_shell *shell)
{
	int		i = 0;
	t_list	*result = NULL;

	while (cmd[i])
	{
		if (is_redirection_operator(cmd[i]))
		{
			ft_lstadd_back(&result, ft_lstnew(ft_strdup(cmd[i])));
			i++;
			if (!cmd[i])
			{
				shell->exit_code = 1;
				ft_lstclear(&result, free);
				return (NULL);
			}
			char *filename = expand_variables_in_token(ft_strdup(cmd[i]), shell);
			if (!filename) {
				ft_lstclear(&result, free);
				return NULL;
			}
			if (strcmp(filename, "") == 0) {
				ft_lstadd_back(&result, ft_lstnew(ft_strdup(cmd[i])));
				free(filename);
				i++;
			} else {
				t_list *wild_lst = process_argument(filename);
				free(filename);
				if (wild_lst) 
				{
					t_list *tmp = wild_lst;
					while (tmp) 
					{
						ft_lstadd_back(&result, ft_lstnew(ft_strdup(tmp->content)));
						tmp = tmp->next;
					}
					ft_lstclear(&wild_lst, free);
				}
				i++;
			}
		}
		else 
		{
			t_list *arg_lst = process_argument(cmd[i]);
			while (arg_lst) {
				ft_lstadd_back(&result, ft_lstnew(ft_strdup(arg_lst->content)));
				arg_lst = arg_lst->next;
			}
			ft_lstclear(&arg_lst, free);
			i++;
		}
	}
	return (result);
}

/* 
 * Expands wildcards in a list of commands and returns the result as an array of strings.
 */
char	**expand_wildcards(char **cmd, t_shell *shell)
{
	t_list	*lst;
	char	**tab;

	lst = expand_wildcards_list(cmd, shell);
	if (!lst)
		return (NULL);
	tab = lst_to_tab(lst);
	ft_lstclear(&lst, free);
	return (tab);
}
