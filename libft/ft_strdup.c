/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:08:44 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/21 19:09:44 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	int		a;
	char	*dest;
	int		longueur;

	a = 0;
	longueur = ft_strlen(s);
	dest = malloc(sizeof(char) * (longueur + 1));
	if (!dest)
		return (NULL);
	while (s[a] != '\0')
	{
		dest[a] = s[a];
		a++;
	}
	dest[a] = '\0';
	return (dest);
}

// int	main(void)
// {
// 	int		a = 0;
// 	char	*dest;
// 	char	*src;

// 	src = "LOLOL;OLOLOLO";
// 	dest = ft_strdup(src);
// 	while (dest[a] != '\0')
// 	{
// 		write(1, &dest[a], 1);
// 		a++;
// 	}
// 	free (dest);
// 	return (0);
// }
