/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:50:53 by lkallio           #+#    #+#             */
/*   Updated: 2020/02/12 09:14:52 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_double.h"

static void		write_sci_suffix(t_pf *pf, t_dbl *dbl)
{
	int		dbl_exponent;

	dbl_exponent = DBL_NEG_EXP ? DBL_NEG_EXP : DBL_POS_EXP;
	TYPE == 15 || TYPE == 17 ? handle_buffer(pf, 'e') : 0;
	TYPE == 16 || TYPE == 18 ? handle_buffer(pf, 'E') : 0;
	if (TYPE > 18)
		TYPE == 19 ? handle_buffer(pf, 'p') : handle_buffer(pf, 'P');
	if (DBL_NEG_EXP > 0)
		handle_buffer(pf, '-');
	else
		handle_buffer(pf, '+');
	handle_buffer(pf, (dbl_exponent / 10) % 10 + '0');
	handle_buffer(pf, dbl_exponent % 10 + '0');
}

void			write_dbl(t_pf *pf, t_dbl *dbl)
{
	int		total_len;

	total_len = DBL_IS_NG + DBL_WHL_LEN
		+ (DBL_MTS_LEN || HASH_FLAG)
		+ DBL_MTS_LEN + !!DBL_IS_SCI * 4 + (TYPE > 18) * 2;
	DBL_BOOLEAN & 1 && ZERO_FLAG ? handle_buffer(pf, '-') : 0;
	if (!(NG_FLAG))
		feedbuf_nchar(pf, ZERO_FLAG ? '0' : ' ', WIDTH - total_len);
	DBL_IS_NG && !(ZERO_FLAG) ? handle_buffer(pf, '-') : 0;
	if (TYPE > 18)
		TYPE == 19 ? feedbuf_str(pf, "0x") : feedbuf_str(pf, "0X");
	feedbuf_str(pf, DBL_WHL_STR);
	DBL_MTS_LEN || HASH_FLAG ? handle_buffer(pf, '.') : 0;
	feedbuf_str(pf, DBL_MTS_STR + !DBL_IS_READJ);
	DBL_IS_SCI ? write_sci_suffix(pf, dbl) : 0;
	if (NG_FLAG)
		feedbuf_nchar(pf, ' ', WIDTH - total_len);
	free(DBL_WHL_STR);
	free(DBL_MTS_STR);
}

int				dbl_hex_char(t_pf *pf, t_dbl *dbl, int num)
{
	if (DBL_IS_HEX && num > 10)
		return (num - 10 + (TYPE == 19 ? 'a' : 'A'));
	else
		return ('0' + num);
}
