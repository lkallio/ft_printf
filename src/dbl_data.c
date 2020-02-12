/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbl_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 14:17:10 by lkallio           #+#    #+#             */
/*   Updated: 2020/02/12 09:14:52 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_double.h"
#include "ft_printf.h"

void	dbl_get_boolean(t_pf *pf, t_dbl *dbl)
{
	DBL_MTS < 0 ? DBL_BOOLEAN |= 1 : 0;
	if (TYPE > 14 && (TYPE > 16 || DBL_NEG_EXP > 4 || DBL_POS_EXP >= PRECISION))
		DBL_BOOLEAN |= 1 << 1;
	if ((TYPE == 15 || TYPE == 16 || TYPE == 19 || TYPE == 20) && !(HASH_FLAG))
		DBL_BOOLEAN |= 1 << 2;
	if (TYPE > 18)
		DBL_BOOLEAN |= 1 << 4;
}

void	dbl_get_data(t_pf *pf, t_dbl *dbl)
{
	long double	dbl_test;

	DBL_BASE = TYPE > 18 ? 16 : 10;
	PRECISION < 0 ? PRECISION = 6 : 0;
	!PRECISION && TYPE > 14 && TYPE < 17 ? PRECISION = 1 : 0;
	dbl_test = (intmax_t)DBL_MTS;
	while ((intmax_t)dbl_test / DBL_BASE && ++DBL_POS_EXP)
		dbl_test /= DBL_BASE;
	dbl_test = 1;
	while (DBL_MTS && dbl_test > DBL_MTS && ++DBL_NEG_EXP)
		dbl_test /= DBL_BASE;
	dbl_get_boolean(pf, dbl);
	while (DBL_IS_SCI && (intmax_t)DBL_MTS / DBL_BASE)
		DBL_MTS /= DBL_BASE;
	while (DBL_MTS && DBL_IS_SCI && !(int)DBL_MTS)
		DBL_MTS *= DBL_BASE;
	if (TYPE > 14 && TYPE < 17)
		PRECISION -= !DBL_NEG_EXP && !DBL_IS_SCI ? DBL_POS_EXP + 1 : 1;
}
