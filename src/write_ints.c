/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ints.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:50:55 by lkallio           #+#    #+#             */
/*   Updated: 2020/02/12 09:50:42 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			hex_char(int num, t_pf *pf, int base)
{
	num = num < 0 ? -num : num;
	if (TYPE == 4)
		return (num);
	if (base == 16 && num >= 10)
		return (num - 10 + (TYPE == 7 ? 'a' : 'A'));
	else
		return ('0' + num);
}

static void			prepend(t_pf *pf)
{
	if (TYPE == 6 && HASH_FLAG)
		handle_buffer(pf, '0');
	else if ((TYPE >= 7 && TYPE <= 10) && HASH_FLAG)
	{
		handle_buffer(pf, '0');
		if (TYPE == 7 || TYPE == 8)
			TYPE == 7 ? handle_buffer(pf, 'x') : handle_buffer(pf, 'X');
		else
			TYPE == 9 ? handle_buffer(pf, 'b') : handle_buffer(pf, 'B');
	}
	else if (PLUS_FLAG && !(PARAMETER & (1 << 5))
			&& TYPE >= 2 && TYPE <= 4)
		handle_buffer(pf, '+');
	else if (PARAMETER & (1 << 5) && TYPE >= 2 && TYPE <= 4)
		handle_buffer(pf, '-');
}

int					write_int(uintmax_t in, t_pf *pf, int base)
{
	if (NG_FLAG && WIDTH > PRECISION && WIDTH--
		&& write_int(in, pf, base))
	{
		if (WDT_COPY-- > NUM_LEN)
			handle_buffer(pf, ' ');
	}
	else if ((in || (IS_ZERO && !(IS_ZERO = 0)))
	&& ++NUM_LEN && write_int(in / base, pf, base))
	{
		if (!(in / base))
			prepend(pf);
		handle_buffer(pf, hex_char(in % base, pf, base));
	}
	else if (PRC_COPY > NUM_LEN && PRC_COPY--
		&& write_int(in, pf, base))
		handle_buffer(pf, '0');
	else if (!(NG_FLAG) && WIDTH > PRECISION && WIDTH > NUM_LEN
	&& WIDTH-- && write_int(in, pf, base))
		ZERO_FLAG ? handle_buffer(pf, '0') : handle_buffer(pf, ' ');
	return (1);
}
