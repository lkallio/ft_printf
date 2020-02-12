/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:50:31 by lkallio           #+#    #+#             */
/*   Updated: 2020/02/12 10:18:49 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_type(t_pf *pf, va_list ap)
{
	if (TYPE == 1)
		return (handle_n(pf, ap));
	else if (TYPE == 0)
	{
		handle_buffer(pf, '%');
		return (1);
	}
	else if (TYPE >= 2 && TYPE <= 3)
		return (handle_int(pf, ap));
	else if (TYPE == 4)
		return (handle_c(pf, ap));
	else if (TYPE >= 5 && TYPE <= 10)
		return (handle_uint(pf, ap));
	else if (TYPE == 11)
		return (handle_str(pf, ap));
	else if (TYPE == 12)
		return (handle_ptr(pf, ap));
	else if (TYPE >= 13)
		return (handle_double(pf, ap));
	return (0);
}

static void	parse_options(t_pf *pf, int *i)
{
	int		cont;
	int		ret;

	cont = 0;
	while ((ret = ft_nstrchr("-+ 0#", pf->format[(*i)])) != -1 && ++(*i))
	{
		cont = 1;
		PARAMETER |= 1 << ret;
	}
	if (pf->format[(*i)] >= '0' && pf->format[(*i)] <= '9' && (cont = 1))
		WIDTH = pf_atoi(pf, i, 0);
	if (pf->format[(*i)] == '.' && ++(*i) && (cont = 1))
		PRECISION = pf_atoi(pf, i, 0);
	if ((ret = ft_nstrchr("hlLzjt", pf->format[(*i)])) != -1)
	{
		cont = 1;
		LENGTH = pf->format[(*i)++];
		if (pf->format[(*i)] == 'h'
					|| pf->format[(*i)] == 'l')
			LENGTH += pf->format[(*i)++];
	}
	if (cont)
		parse_options(pf, i);
}

static void	parse_argument(t_pf *pf, int *i, va_list ap)
{
	int		ret;

	++(*i);
	parse_options(pf, i);
	if ((ret = ft_nstrchr("%ndicuoxXbBspfFgGeEaA", pf->format[(*i)])) != -1
	&& ++(*i))
	{
		TYPE = ret;
		handle_type(pf, ap);
	}
}

static int	parse_quoted(t_pf *pf, va_list ap)
{
	int		i;
	int		j;

	i = 0;
	while (pf->format[i])
	{
		if (pf->format[i] == '%')
		{
			j = -1;
			while (++j < 9)
				pf->dt[j] = 0;
			PRECISION = -1;
			WIDTH = -1;
			parse_argument(pf, &i, ap);
			continue ;
		}
		handle_buffer(pf, pf->format[i++]);
	}
	write(1, pf->buf, pf->buf_idx);
	return (1);
}

int			ft_printf(char const *format, ...)
{
	t_pf	pf;
	va_list	ap;

	va_start(ap, format);
	pf = (t_pf){.dt = {0, -1, -1, 0, 0, 0, 0, 0, 0}, .buf = {0},
		.buf_idx = 0, .n = 0, .format = format, .tempstr = 0};
	parse_quoted(&pf, ap);
	va_end(ap);
	return (pf.n + pf.buf_idx);
}
