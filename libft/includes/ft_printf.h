/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicolon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 00:23:48 by rmicolon          #+#    #+#             */
/*   Updated: 2016/03/22 00:32:28 by rmicolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <wchar.h>
# include "libft.h"

typedef unsigned long long t_ull;

typedef struct		s_pf
{
	int				fd;
	long long		i;
	t_ull			u;
	long double		f;
	wchar_t			lc;
	char			*s;
	wchar_t			*ls;
	int				*n;
	const char		*fmt;
	va_list			argp;
	char			maj;
	int				ret;
	char			brk;
	char			len;
	char			dot;
	char			ts;
	int				tsc;
	int				nsize;
	int				prec;
	int				width;
	char			sharp;
	char			zero;
	char			minus;
	char			plus;
	char			space;
	char			neg;
	char			*chr;
	unsigned int	mask[3];
}					t_pf;

typedef struct		s_fptr
{
	char			op;
	void			(*ptr)(t_pf*);
}					t_fptr;

int					ft_printf(const char *restrict format, ...);
void				fconv_init(t_fptr *fptr);
void				fpre_init(t_fptr *fptr);
void				struct_init(t_pf *pf, const char *restrict format);
void				ft_print_di(t_pf *pf);
void				ft_print_dup(t_pf *pf);
void				ft_print_o(t_pf *pf);
void				ft_print_oup(t_pf *pf);
void				ft_print_u(t_pf *pf);
void				ft_print_uup(t_pf *pf);
void				ft_print_x(t_pf *pf);
void				ft_print_xup(t_pf *pf);
void				ft_print_c(t_pf *pf);
void				ft_print_cup(t_pf *pf);
void				ft_print_s(t_pf *pf);
void				ft_print_sup(t_pf *pf);
void				ft_print_p(t_pf *pf);
void				ft_print_b(t_pf *pf);
void				ft_print_m(t_pf *pf);
void				ft_print_n(t_pf *pf);
void				ft_print_bad_conv(t_pf *pf);
void				ft_print_percent(t_pf *pf);
void				ft_set_fd(t_pf *pf);
void				ft_print_f(t_pf *pf);
t_ull				ft_stou(long long nb, t_pf *pf);
long double			ft_dtold(double nb, t_pf *pf);
long double			ft_ldtold(long double nb, t_pf *pf);
void				ft_flags(t_pf *pf);
void				ft_width(t_pf *pf);
void				ft_precision(t_pf *pf);
void				ft_lenght(t_pf *pf);
void				ft_pre_unumflags(t_ull nb, char base, t_pf *pf);
void				ft_pre_numflags(t_ull nb, char base, t_pf *pf);
void				ft_pre_floatflags(long double nb, t_pf *pf);
void				ft_pre_strflags(char *str, t_pf *pf);
void				ft_pre_wstrflags(wchar_t *str, t_pf *pf);
void				ft_pre_charflags(t_pf *pf);
void				ft_pre_wcharflags(wchar_t c, t_pf *pf);
void				ft_post_strflags(char *str, t_pf *pf);
void				ft_post_wstrflags(wchar_t *str, t_pf *pf);
void				ft_post_charflags(t_pf *pf);
void				ft_post_wcharflags(wchar_t c, t_pf *pf);
void				ft_post_numflags(t_ull nb, char base, t_pf *pf);
void				ft_post_floatflags(long double nb, t_pf *pf);
void				struct_reset(t_pf *pf);
void				ft_print_charwidth(t_pf *pf);
void				ft_print_floatwidth(long double nb, t_pf *pf);
void				ft_print_numwidth(t_ull nb, char base, t_pf *pf);
void				ft_print_wstrwidth(wchar_t *str, t_pf *pf);
void				ft_print_strwidth(char *str, t_pf *pf);
void				ft_print_numprec(t_ull nb, char base, t_pf *pf);
void				ft_printfloat(long double nb, t_pf *pf);
void				ft_print_zeros(char base, t_pf *pf);
void				ft_printhex(t_pf *pf);
void				ft_printnbr(t_ull nb, char base, t_pf *pf);
void				ft_printchar(char c, t_pf *pf);
void				ft_printwchar(wchar_t c, t_pf *pf);
void				ft_printstr(char *str, t_pf *pf);
void				ft_printwstr(wchar_t *str, t_pf *pf);
void				ft_printit(wchar_t c, unsigned int value, int s, t_pf *pf);
int					ft_wwidthlen(wchar_t *str);
int					ft_wideprec(wchar_t *str, t_pf *pf);
int					ft_bitsize(unsigned int nbr);
void				ft_nsize(unsigned long long nb, char base, t_pf *pf);
void				ft_print_prefix(char *str, t_pf *pf);

#endif
