/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcards3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 00:08:46 by throbert          #+#    #+#             */
/*   Updated: 2025/02/24 00:28:41 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* Checks if the entry should be skipped based on conditions */
int should_skip_entry(struct dirent *entry, int show_hidden)
{
	return (
		!entry || 
		(!show_hidden && entry->d_name[0] == '.') || 
		(!strcmp(entry->d_name, ".") || 
		(!strcmp(entry->d_name, ".."))));
}

/* Handles matching a character in pattern and string */
int handle_char_match(char *patt, char *str, int *p, int *s)
{
	if (patt[*p] == str[*s])
	{
		(*p)++;
		(*s)++;
		return (1);
	}
	return (0);
}

/* Handles the '*' wildcard pattern */
int handle_star(char *pattern, t_wildcard *wc)
{
	if (pattern[wc->p] == '*')
	{
		wc->star = wc->p;
		wc->match = wc->s;
		wc->p++;
		return (1);
	}
	return (0);
}

/* Handles backtracking for wildcard matching */
int handle_backtrack(t_wildcard *wc)
{
	if (wc->star != -1)
	{
		wc->p = wc->star + 1;
		wc->match++;
		wc->s = wc->match;
		return (1);
	}
	return (0);
}

/* Recursively matches a pattern in directories */
static int recursive_match(char *pattern, char *name)
{
	DIR *dir;
	struct dirent *entry;
	int match_found = 0;

	if (wildcard_match(pattern, name, NULL))
		return 1;

	dir = opendir(name);
	if (!dir) return 0;

	entry = readdir(dir);
	while (entry)
	{
		if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
		{
			char *subpath = build_full_path(name, entry->d_name);
			if (recursive_match(pattern, subpath))
				match_found = 1;
			free(subpath);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return match_found;
}

/* Checks if there are any remaining non-wildcard characters in the pattern */
int check_remaining(char *pattern)
{
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0');
}

/* Main function to match wildcards in the pattern */
int wildcard_match(char *pattern, char *str, t_wildcard *wc)
{
	t_wildcard wc_local;

	if (!wc) {
		wc = &wc_local;
		wc->s = 0;
		wc->p = 0;
		wc->star = -1;
		wc->match = 0;
	}
	else {
		wc->s = 0;
		wc->p = 0;
		wc->star = -1;
		wc->match = 0;
	}

	if (strncmp(pattern, "**/", 3) == 0) {
		return recursive_match(pattern + 3, str);
	}
	else if (strcmp(pattern, "**") == 0) {
		return 1;
	}
	while (str[wc->s] || pattern[wc->p] == '*')
	{
		if (handle_char_match(pattern, str, &wc->p, &wc->s))
		{
			// Just proceed to the next iteration
		}
		else if (handle_star(pattern, wc))
		{
			// Just proceed to the next iteration
		}
		else if (pattern[wc->p] == '[')
		{
			int match = 0;
			int invert = 0;
			wc->p++;
		
			if (pattern[wc->p] == '^' || pattern[wc->p] == '!') {
				invert = 1;
				wc->p++;
			}
		
			while (pattern[wc->p] != ']' && pattern[wc->p] != '\0') 
			{
				if (pattern[wc->p + 1] == '-' && 
					pattern[wc->p + 2] != ']' && 
					pattern[wc->p + 2] != '\0') 
				{
					if (str[wc->s] >= pattern[wc->p] && 
						str[wc->s] <= pattern[wc->p + 2])
						match = 1;
					wc->p += 3;
				} 
				else 
				{
					if (pattern[wc->p] == str[wc->s])
						match = 1;
					wc->p++;
				}
			}

			if (invert)
			{
				if (!match)
					return 0;
			}
			else
			{
				if (!match)
					return 0;
			}
			
			wc->s++;
		}
		else if (handle_backtrack(wc))
		{
			// Just proceed to the next iteration
		}
		else
			return 0;
	}
	return (check_remaining(&pattern[wc->p]));
}
