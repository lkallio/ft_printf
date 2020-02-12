/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ints.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:50:45 by lkallio           #+#    #+#             */
/*   Updated: 2020/02/12 10:32:45 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static intmax_t		int_length(t_pf *pf, va_list ap)
{
	if (!LENGTH)
		return (va_arg(ap, int));
	else if (LENGTH == 'l')
		return (va_arg(ap, long));
	else if (LENGTH == 'l' + 'l')
		return (va_arg(ap, long long));
	else if (LENGTH == 'z')
		return (va_arg(ap, size_t));
	else if (LENGTH == 'j')
		return (va_arg(ap, intmax_t));
	else if (LENGTH == 'h')
		return ((short)va_arg(ap, int));
	else if (LENGTH == 'h' + 'h')
		return ((char)va_arg(ap, int));
	else
		return (-1);
}

static uintmax_t	uint_length(t_pf *pf, va_list ap)
{
	if (!LENGTH)
		return (va_arg(ap, unsigned int));
	else if (LENGTH == 'l')
		return (va_arg(ap, unsigned long));
	else if (LENGTH == 'l' + 'l')
		return (va_arg(ap, unsigned long long));
	else if (LENGTH == 'z')
		return (va_arg(ap, size_t));
	else if (LENGTH == 'j')
		return (va_arg(ap, uintmax_t));
	else if (LENGTH == 'h')
		return ((unsigned short)va_arg(ap, int));
	else if (LENGTH == 'h' + 'h')
		return ((unsigned char)va_arg(ap, int));
	else
		return (-1);
}

int					handle_ptr(t_pf *pf, va_list ap)
{
	PARAMETER |= (1 << 4);
	TYPE = 7;
	LENGTH = 'l';
	return (handle_uint(pf, ap));
}

int					handle_int(t_pf *pf, va_list ap)
{
	intmax_t	in;

	PRC_COPY = PRECISION;
	WDT_COPY = WIDTH;
	if ((in = int_length(pf, ap)) == (intmax_t)-1)
		return (0);
	if (!in)
	{
		IS_ZERO++;
		PARAMETER &= ~(1 << 4);
	}
	if (PLUS_FLAG || SPACE_FLAG
		|| HASH_FLAG
		|| in < 0)
		NUM_LEN++;
	in < 0 && (PARAMETER |= (1 << 5)) ? in *= -1 : 0;
	write_int(in, pf, 10);
	return (1);
}

int					handle_uint(t_pf *pf, va_list ap)
{
	uintmax_t	in;

	PRC_COPY = PRECISION;
	WDT_COPY = WIDTH;
	if ((in = uint_length(pf, ap)) == (uintmax_t)-1)
		return (0);
	if (!in)
	{
		IS_ZERO++;
		PARAMETER &= ~(1 << 4);
	}
	if (TYPE > 5 && (SPACE_FLAG
		|| HASH_FLAG))
		TYPE == 7 || TYPE == 8 ? NUM_LEN += 2 : NUM_LEN++;
	if (TYPE == 6 || TYPE == 7 || TYPE == 8)
		TYPE == 6 ? write_int(in, pf, 8) : write_int(in, pf, 16);
	else
		TYPE == 9 || TYPE == 10 ? write_int(in, pf, 2) : write_int(in, pf, 10);
	return (1);
}
