/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_n_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:50:48 by lkallio           #+#    #+#             */
/*   Updated: 2020/02/12 10:30:52 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_strlen(char *s)
{
	return (!*s ? 0 : 1 + ft_strlen(s + 1));
}

int				handle_str(t_pf *pf, va_list ap)
{
	char		*print;
	int			arg_len;
	static char	null[] = "(null)";

	PRC_COPY = PRECISION;
	if (!(print = va_arg(ap, char *)))
		print = null;
	arg_len = ft_strlen(print);
	arg_len = arg_len > PRECISION && PRECISION != -1 ? PRECISION : arg_len;
	print[arg_len] = 0;
	if (NG_FLAG)
		feedbuf_str(pf, print);
	feedbuf_nchar(pf, ' ', WIDTH - arg_len);
	if (!(NG_FLAG))
		feedbuf_str(pf, print);
	return (1);
}

int				handle_n(t_pf *pf, va_list ap)
{
	int		*target;

	target = va_arg(ap, int *);
	*target = pf->n + pf->buf_idx;
	return (1);
}

int				handle_c(t_pf *pf, va_list ap)
{
	char	c;

	c = (char)va_arg(ap, int);
	handle_buffer(pf, c);
	return (1);
}