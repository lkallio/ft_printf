/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:50:42 by lkallio           #+#    #+#             */
/*   Updated: 2020/01/15 14:10:33 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_double.h"

static int		handle_mts_malloc(t_dbl *dbl, int i)
{
	if (!(DBL_MTS_STR = (char *)malloc(i + 2)))
		return (-1);
	DBL_MTS_STR[i + 1] = 0;
	DBL_MTS_LEN = i;
	return ((int)(DBL_MTS * 10) > 4);
}

static int		handle_mantissa(t_pf *pf, t_dbl *dbl, int i)
{
	int		out;
	int		ret;

	if (PRECISION > 0)
	{
		DBL_MTS *= DBL_BASE;
		out = (int)DBL_MTS;
		DBL_MTS -= (int)DBL_MTS;
		(DBL_NEG_EXP <= i || TYPE < 15 || DBL_IS_SCI) ? PRECISION-- : 0;
		ret = handle_mantissa(pf, dbl, i + 1);
	}
	else
		return (handle_mts_malloc(dbl, i));
	if (ret == -1)
		return (-1);
	ret > 0 ? out++ : 0;
	if ((i == DBL_MTS_LEN - 1) && DBL_NOTRAIL && !(out % DBL_BASE) && DBL_MTS_LEN--)
		DBL_MTS_STR[i + 1] = 0;
	else
		DBL_MTS_STR[i + 1] = dbl_hex_char(pf, dbl, out % DBL_BASE);
	return (out / DBL_BASE);
}

static int		handle_whole(t_pf *pf, t_dbl *dbl, intmax_t in, int i, int j)
{
	if (i)
	{
		if (handle_whole(pf, dbl, in / DBL_BASE, i - 1, j + 1) == -1)
			return (-1);
	}
	else
	{
		DBL_WHL_LEN = j + !j;
		if (!(DBL_WHL_STR = (char *)malloc(j + 1)))
			return (-1);
		DBL_WHL_STR[j] = 0;
	}
	DBL_WHL_STR[i] = dbl_hex_char(pf, dbl, in % DBL_BASE);
	return (1);
}

static int		dbl_make_printables(t_pf *pf, t_dbl *dbl)
{
	int ret;

	if ((ret = handle_mantissa(pf, dbl, 0)) == -1)
		return (0);
	if (ret > 0)
		++DBL_WHL && !((intmax_t)DBL_WHL % DBL_BASE) ? DBL_POS_EXP++ : 0;
	if (DBL_IS_SCI && (int)DBL_WHL / DBL_BASE && (DBL_BOOLEAN |= (1 << 3)))
	{
		DBL_MTS_STR[0] = '0';
		DBL_MTS_LEN++;
		DBL_WHL /= DBL_BASE;
	}
	if (handle_whole(pf, dbl, (intmax_t)DBL_WHL,
	DBL_IS_SCI ? 0 : DBL_POS_EXP, 0) == -1)
	{
		free(DBL_MTS_STR);
		return (0);
	}
	return (1);
}

int				handle_double(t_pf *pf, va_list ap)
{
	t_dbl	dbl;

	dbl = (t_dbl){.in = {0}, .data = {0}, .whole = 0, .mantissa = 0};
	if (LENGTH == 'L')
		dbl.in[1] = va_arg(ap, long double);
	else
		dbl.in[1] = (long double)va_arg(ap, double);
	dbl_get_data(pf, &dbl);
	dbl.in[1] < 0 && (dbl.data[3] |= 1) ? dbl.in[1] *= -1 : 0;
	dbl.in[0] = (intmax_t)dbl.in[1];
	dbl.in[1] -= (intmax_t)dbl.in[1];
	if (!dbl_make_printables(pf, &dbl))
		return (-1);
	write_dbl(pf, &dbl);
	return (1);
}
