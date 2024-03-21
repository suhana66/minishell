/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:06:17 by susajid           #+#    #+#             */
/*   Updated: 2024/03/21 10:06:18 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	const char	*srcstart;

	srcstart = src;
	if (dstsize)
	{
		while (*src && dstsize - 1)
		{
			*dst++ = *src++;
			dstsize--;
		}
		*dst = 0;
	}
	while (*src)
		src++;
	return ((size_t)(src - srcstart));
}
