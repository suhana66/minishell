/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: susajid <susajid@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:14:59 by susajid           #+#    #+#             */
/*   Updated: 2024/03/19 11:37:36 by susajid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_format(int *result, char *s, va_list *args);
void	ft_print_chars(int *count, char *s, int len);
void	ft_print_unsigned(int *count, unsigned long long n,
			unsigned long long base, char replace_c);
void	ft_print_int(int *count, int n, int sign);

int	ft_printf(const char *s, ...)
{
	int		result;
	va_list	args;

	result = 0;
	va_start(args, s);
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			if (!*s)
				break ;
			print_format(&result, (char *)s, &args);
		}
		else
			ft_print_chars(&result, (char *)s, 1);
		if (result < 0)
			break ;
		s++;
	}
	va_end(args);
	return (result);
}

void	print_format(int *result, char *s, va_list *args)
{
	char	var;

	if (*s == 'c')
	{
		var = va_arg(*args, int);
		ft_print_chars(result, &var, 1);
	}
	else if (*s == 's')
		ft_print_chars(result, va_arg(*args, char *), -1);
	else if (*s == 'p')
	{
		ft_print_chars(result, "0x", -1);
		ft_print_unsigned(result, va_arg(*args, unsigned long long), 16, 'a');
	}
	else if (*s == 'd' || *s == 'i')
		ft_print_int(result, va_arg(*args, int), 0);
	else if (*s == 'u')
		ft_print_unsigned(result, va_arg(*args, unsigned int), 10, 0);
	else if (*s == 'x')
		ft_print_unsigned(result, va_arg(*args, unsigned int), 16, 'a');
	else if (*s == 'X')
		ft_print_unsigned(result, va_arg(*args, unsigned int), 16, 'A');
	else if (*s == '%')
		ft_print_chars(result, s, 1);
}

void	ft_print_chars(int *count, char *s, int len)
{
	if (!s)
		s = "(null)";
	while ((len < 0 && *s) || len > 0)
	{
		if (write(1, s, 1) < 0)
		{
			*count = -1;
			return ;
		}
		(*count)++;
		len--;
		s++;
	}
}

void	ft_print_unsigned(int *count, unsigned long long n,
	unsigned long long base, char replace_c)
{
	char	digit;

	if (n >= base)
		ft_print_unsigned(count, n / base, base, replace_c);
	if (*count < 0)
		return ;
	digit = (n % base) + '0';
	if (replace_c && digit > '9')
		digit = digit - '9' + replace_c - 1;
	ft_print_chars(count, &digit, 1);
}

void	ft_print_int(int *count, int n, int sign)
{
	char	digit;

	if (!sign)
	{
		if (n < 0)
		{
			ft_print_chars(count, "-", 1);
			sign = -1;
		}
		else
			sign = 1;
	}
	if ((n >= 10 && sign == 1) || (n <= -10 && sign < 0))
		ft_print_int(count, n / 10, sign);
	if (*count < 0)
		return ;
	digit = n % 10 * sign + '0';
	ft_print_chars(count, &digit, 1);
}
