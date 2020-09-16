/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:42:01 by alienard          #+#    #+#             */
/*   Updated: 2020/09/16 17:47:16 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')
			|| ('0' <= c && c <= '9')
			|| (ft_ischarset(EXT_ALPHA_MAJ, c))
			|| (ft_ischarset(EXT_ALPHA_MIN, c)))
		return (1);
	else
		return (0);
}
