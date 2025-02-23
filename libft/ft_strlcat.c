/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: throbert <throbert@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 03:03:35 by rbardet-          #+#    #+#             */
/*   Updated: 2025/02/21 19:11:45 by throbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	a;
	size_t	b;
	size_t	c;
	size_t	d;

	a = 0;
	b = 0;
	c = 0;
	while (dest[a] != '\0' && a < size)
		a++;
	while (src[b] != '\0')
		b++;
	if (size <= a)
		return (a + b);
	d = a;
	while (src[c] != '\0' && (d + 1) < size)
	{
		dest[d] = src[c];
		d++;
		c++;
	}
	dest[d] = '\0';
	return (a + b);
}
// int main(void)
// {
// 	char source[]="pqrstuvwxyz";
// 	char destination[] = "";
// 	printf("%s\n", source);
// 	printf("%s\n", destination);
// 	ft_strlcat(destination, source, 1);
// 	printf("%s\n", source);
// 	printf("%s", destination);
// 	return(0);
// }
