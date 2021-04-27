/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:50:50 by lkallio           #+#    #+#             */
/*   Updated: 2021/04/27 19:30:17 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_nstrchr(const char *pool, char c)
{
	int	i;

	i = -1;
	while (pool[++i])
		if (pool[i] == c)
			return (i);
	return (-1);
}

int	pf_atoi(t_pf *pf, int *i, int ret)
{
	if (pf->format[(*i)] >= '0' && pf->format[(*i)] <= '9')
	{
		ret = ret * 10 + pf->format[(*i)++] - '0';
		return (pf_atoi(pf, i, ret));
	}
	return (ret);
}

int	ft_itrn(int arg, int ret1, int ret2)
{
	if (arg)
		return (ret1);
	return (ret2);
}

int	ft_intass(int *ass, int dst)
{
	*ass = dst;
	return (*ass);
}

size_t	ft_strlen(const char *str)
{
	if (!*str)
		return (0);
	return (1 + ft_strlen(++str));
}

char	*ft_stern(int true, char *s1, char *s2)
{
	if (true)
		return (s1);
	return (s2);
}
