/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:20:56 by nickras           #+#    #+#             */
/*   Updated: 2023/01/20 11:02:06 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft/libft.h"

long long	handle_long_long(long long i);
int			handler(const char *s, int i, va_list args);
int			ft_printf(const char *s, ...);
int			handle_char(int c);
int			handle_string(char *str);
int			handle_decimal(int i);
int			ft_uitoa(unsigned int n);
int			ft_hexa(unsigned int n);
int			longhexa(unsigned long n);
int			ft_hexaul(unsigned long n);
int			ft_hexau(unsigned int n);

#endif