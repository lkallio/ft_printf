/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkallio <lkallio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 12:51:48 by lkallio           #+#    #+#             */
/*   Updated: 2020/02/12 09:48:12 by lkallio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <string.h>
# include <inttypes.h>
# include <stdlib.h>

# define PARAMETER	pf->dt[0]
# define WIDTH		pf->dt[1]
# define PRECISION	pf->dt[2]
# define LENGTH		pf->dt[3]
# define TYPE		pf->dt[4]
# define NUM_LEN	pf->dt[5]
# define PRC_COPY	pf->dt[6]
# define WDT_COPY	pf->dt[7]
# define IS_ZERO	pf->dt[8]

# define NG_FLAG	pf->dt[0] & 1
# define PLUS_FLAG	pf->dt[0] & (1 << 1)
# define SPACE_FLAG	pf->dt[0] & (1 << 2)
# define ZERO_FLAG	pf->dt[0] & (1 << 3)
# define HASH_FLAG	pf->dt[0] & (1 << 4)

typedef struct		s_pf
{
	int				dt[9];
	char			buf[1024];
	int				buf_idx;
	int				n;
	const char		*format;
	char			*tempstr;
}					t_pf;

int					handle_double(t_pf *pf, va_list ap);
void				feedbuf_nchar(t_pf *pf, char ins, int n);
void				feedbuf_str(t_pf *pf, char *str);
void				handle_buffer(t_pf *pf, char ins);
int					write_int(uintmax_t in, t_pf *pf, int base);
int					ft_nstrchr(const char *pool, char c);
int					handle_str(t_pf *pf, va_list ap);
int					handle_uint(t_pf *pf, va_list ap);
int					handle_int(t_pf *pf, va_list ap);
int					handle_ptr(t_pf *pf, va_list ap);
int					ft_printf(char const *format, ...);
int					handle_n(t_pf *pf, va_list ap);
int					ft_nstrchr(const char *pool, char c);
int					pf_atoi(t_pf *pf, int *i, int ret);
int					handle_c(t_pf *pf, va_list ap);

#endif
