/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:50:50 by lkallio           #+#    #+#             */
/*   Updated: 2020/01/15 12:52:35 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_buffer(t_pf *pf, char ins)
{
	if (pf->buf_idx == 1024)
	{
		write(1, pf->buf, 1024);
		pf->n += 1024;
		pf->buf_idx = 0;
	}
	pf->buf[(pf->buf_idx)++] = ins;
}

void	feedbuf_str(t_pf *pf, char *str)
{
	while (*str)
		handle_buffer(pf, *str++);
}

void	feedbuf_nchar(t_pf *pf, char ins, int n)
{
	if (n < 0)
		return ;
	while (n--)
		handle_buffer(pf, ins);
}

int		ft_nstrchr(const char *pool, char c)
{
	int		i;

	i = -1;
	while (pool[++i])
		if (pool[i] == c)
			return (i);
	return (-1);
}

int		pf_atoi(t_pf *pf, int *i, int ret)
{
	if (pf->format[(*i)] == '-' && (*i)++)
		return (-pf_atoi(pf, i, ret));
	if (pf->format[(*i)] >= '0' && pf->format[(*i)] <= '9')
	{
		ret = ret * 10 + pf->format[(*i)++] - '0';
		return (pf_atoi(pf, i, ret));
	}
	return (ret);
}
