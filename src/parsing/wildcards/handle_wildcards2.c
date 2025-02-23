/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcards2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:28:41 by throbert          #+#    #+#             */
/*   Updated: 2025/02/24 00:16:35 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Checks if the given path is a directory */
int is_directory(char *path)
{
	struct stat st;
	if (stat(path, &st) != 0)
		return 0;
	return S_ISDIR(st.st_mode);
}

/* Returns 1 if the string contains wildcard characters ('*', '?', or '[') */
int contains_wildcard(char *str)
{
	int i;
	int in_single;
	int in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		else if ((str[i] == '*' || str[i] == '?' || str[i] == '[') 
				&& !in_single && !in_double)
			return (1);
		i++;
	}
	return (0);
}

/* Creates a new node from the given entry name */
t_list *create_node_from_entry(char *entry_name, t_list **lst)
{
	t_list *new_node;

	new_node = ft_lstnew(ft_strdup(entry_name));
	if (!new_node)
	{
		ft_lstclear(lst, free);
	}
	return (new_node);
}

/* Joins three strings together into one string */
char *ft_strjoin3(char *s1, char *s2, char *s3)
{
	char *result;
	size_t total_len;
	size_t current_len;

	if (!s1 || !s2 || !s3)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	result = malloc(total_len * sizeof(char));
	if (!result)
		return (NULL);
	current_len = 0;
	ft_strlcpy(result + current_len, s1, total_len - current_len);
	current_len += ft_strlen(s1);
	ft_strlcpy(result + current_len, s2, total_len - current_len);
	current_len += ft_strlen(s2);
	ft_strlcpy(result + current_len, s3, total_len - current_len);
	return (result);
}

/* Builds the full path by joining base and name */
char *build_full_path(char *base, char *name)
{
	if (!base || !name) return NULL;
	
	char *path;
	if (strcmp(base, "/") == 0)
		path = ft_strjoin("/", name);
	else if (strcmp(base, ".") == 0)
		path = ft_strdup(name);
	else 
		path = ft_strjoin3(base, "/", name);
	
	return path;
}
