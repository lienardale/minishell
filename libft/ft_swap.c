/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:43:32 by alienard          #+#    #+#             */
/*   Updated: 2020/06/04 14:28:54 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap_int(int *a, int *b)
{
	int	c;

	c = *a;
	*a = *b;
	*b = c;
}

void	ft_swap_double(double *a, double *b)
{
	double	c;

	c = *a;
	*a = *b;
	*b = c;
}

void	ft_swap_addr(void **a, void **b)
{
	void	*c;
	
	c = *a;
	*a = *b;
	*b = c;
}
