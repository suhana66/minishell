/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:28:48 by susajid           #+#    #+#             */
/*   Updated: 2024/03/19 17:48:35 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	c = c % 256;
	if (!s)
		return (NULL);
	while (1)
	{
		if (*s == c)
			return ((char *)(s));
		if (!*s)
			break ;
		s++;
	}
	return (NULL);
}
