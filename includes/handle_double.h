/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:51:51 by lkallio           #+#    #+#             */
/*   Updated: 2020/01/15 14:07:28 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_DOUBLE_H
# define HANDLE_DOUBLE_H

# include "ft_printf.h"

# define DBL_POS_EXP		dbl->data[0]
# define DBL_BASE			dbl->data[1]
# define DBL_NEG_EXP		dbl->data[2]
# define DBL_BOOLEAN		dbl->data[3]
# define DBL_MTS_LEN		dbl->data[4]
# define DBL_WHL_LEN		dbl->data[5]

# define DBL_IS_NG			(dbl->data[3] & 1)
# define DBL_IS_SCI			(dbl->data[3] & (1 << 1))
# define DBL_NOTRAIL		(dbl->data[3] & (1 << 2))
# define DBL_IS_READJ		(dbl->data[3] & (1 << 3))
# define DBL_IS_HEX			(dbl->data[3] & (1 << 4))

typedef struct				s_dbl
{
	long double				in[2];
	int						data[6];
	char					*whole;
	char					*mantissa;
}							t_dbl;

# define DBL_WHL			(dbl->in[0])
# define DBL_MTS			(dbl->in[1])
# define DBL_WHL_STR		(dbl->whole)
# define DBL_MTS_STR		(dbl->mantissa)

void			dbl_get_data(t_pf *pf, t_dbl *dbl);
void			write_dbl(t_pf *pf, t_dbl *dbl);
int				dbl_hex_char(t_pf *pf, t_dbl *dbl, int num);

#endif
